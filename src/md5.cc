#include <stdio.h>
#include <string>

#include <openssl/md5.h>
#include <boost/foreach.hpp>
#include <boost/algorithm/string.hpp>


std::string md5(unsigned char* ptr, size_t size) {
    char output[32 + 1];
    unsigned char digest[16];
    const char *fmt =
        "%02x%02x%02x%02x%02x%02x%02x%02x"
        "%02x%02x%02x%02x%02x%02x%02x%02x";

    MD5((const unsigned char*)ptr, size, digest);

    snprintf(output,
        sizeof(output)/sizeof(output[0]), 
        fmt, 
        digest[0], digest[1], digest[2], digest[3],
        digest[4], digest[5], digest[6], digest[7],
        digest[8], digest[9], digest[10], digest[11],
        digest[12], digest[13], digest[14], digest[15]
    );

    return output;
}


bool check(unsigned char* target_ptr, size_t target_size, unsigned char* signature_ptr, size_t signature_size) {
    bool has_hit = false;
    
    unsigned char digest[MD5_DIGEST_LENGTH];
    std::string target = md5(target_ptr, target_size);
    std::cout << "target     : " << target << std::endl;

    std::string signature(reinterpret_cast<char const*>(signature_ptr), signature_size -1);
    std::list<std::string> signatures_list;

    boost::split(signatures_list, signature, boost::is_any_of("\n"));
    BOOST_FOREACH(signature, signatures_list) {
        has_hit |= signature == target;
    }         

    return has_hit;
}

extern "C" {
    bool scan(unsigned char* target, size_t target_size, unsigned char* signature, size_t signature_size) {
        return check(target, target_size, signature, signature_size);
    }
}

