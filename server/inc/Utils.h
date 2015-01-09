/*
 * Utils.h
 *
 *  Created on: Apr 9, 2013
 *      Author: nhsan
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <boost/xpressive/xpressive.hpp>
#include <uuid/uuid.h>
#include "boost/archive/iterators/base64_from_binary.hpp"
#include "boost/archive/iterators/binary_from_base64.hpp"
#include "boost/archive/iterators/transform_width.hpp"
#include <boost/algorithm/string.hpp>

#include <boost/algorithm/string.hpp>
using namespace boost::algorithm;

using namespace std;
using namespace boost::xpressive;
using namespace boost::archive::iterators;
#include <glog/logging.h>

namespace
{

class Utils
{
public:

	static string generate_code(int len)
	{
		static const char alphanum[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
		string code = "";
		if (len <= 0 || len >= 32) return code;

		srand(time(NULL));

		for (int i = 0; i < len; i++)
		{
			code += alphanum[rand() % (sizeof(alphanum) - 1)];
		}
		return code;
	}

	/*
	 * get hash code from a buffer terminated by '\0'
	 */
	inline static uint32_t hash_code(const char* s)
	{
		uint32_t h = *s;
		if (h) for (++s; *s; ++s)
		{
			h = (h << 5) - h + *s;
		}
		return h;
		//		uint32_t ret;
		//		MurmurHash3_x86_32(s, strlen(s),0, &ret);
		//		return ret;
	}

	/*
	 * check email format
	 * Note: use regular expression
	 */
	static bool normalize_email(string &email)
	{
		static sregex rex = sregex::compile("(\\w+)(\\.)*(\\w*)@(\\w+)(\\.(\\w+))+");
		if (email.empty()) return false;
		boost::algorithm::to_lower(email);

		if (regex_match(email, rex)) return true;
		else return false;
	}

	static bool check_password(string &pwd)
	{
		/*TODO: implement*/
		return true;
	}

	/*
	 * Check and normalize telephone number
	 */
	static bool normalize_tel(string &tel)
	{
		static sregex rex = sregex::compile("(\\+84)(9(\\d{8})|(1\\d{9}))");
		static sregex rex1 = sregex::compile("((09\\d{8})|(01\\d{9}))");

		if (tel.empty()) return false;
		if (regex_match(tel, rex)) return true;
		if (regex_match(tel, rex1))
		{
			tel = tel.erase(0, 1);
			tel = tel.insert(0, "+84");
			return true;
		}
		else return false;
	}

	static bool is_valid_url(string url)
	{
		return true;
	}
	/*
	 * Validate DOB ( Date Of Birth )
	 */
	static bool is_valid_dob(string dob)
	{
		/* dd-mm-yyyy format */
		static sregex rex = sregex::compile("((0[1-9])|([12][0-9])|(3[01]))[- /.]((0[1-9])|(1[012]))[- /.](19|20)(\\d\\d)");
		if (dob.empty()) return false;

		if (regex_match(dob, rex)) return true;
		else return false;
	}

	static bool normalize_dob(string &dob)
	{
		trim(dob);
		if (dob.empty()) return false;

		/* dd-mm-yyyy format */
		static sregex rex = sregex::compile("((0[1-9])|([12][0-9])|(3[01]))[- /.]((0[1-9])|(1[012]))[- /.](19|20)(\\d\\d)");

		if (regex_match(dob, rex)) return true;
		else return false;
	}

	static bool is_valid_reg_time(string dob)
	{

		// TODO: check reg_time in format dd/mm/yyyy
		return true;
	}

	static bool is_valid_reg_deadline_time(string dob)
	{

		// TODO: check reg_deadline_time
		return true;
	}

	static bool normalize_time(string &time)
	{
		return true;
	}

	/*
	 * 	Validate password
	 */
	static bool is_valid_password(string password)
	{
		return true;
	}

	static string pack_uuid(const uuid_t &uuid)
	{
		uuid_t out;
		out[0] = uuid[6];
		out[1] = uuid[7];

		out[2] = uuid[4];
		out[3] = uuid[5];

		out[4] = uuid[0];
		out[5] = uuid[1];
		out[6] = uuid[2];
		out[7] = uuid[3];
		memcpy(out + 8, uuid + 8, 8);
		return string((char*) out, 16);
	}

	/*
	 * Generate session ID using UUID
	 */
	static string uuid_encode(string id)
	{
		static const char* _keyStr = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_=";
		unsigned char* input = (unsigned char*) id.c_str();
		unsigned char output[32];
		uint chr1, chr2, chr3, enc1, enc2, enc3, enc4;
		int i = 0;
		int j = 0;

		while (i < 16)
		{
			chr1 = input[i++];
			enc1 = chr1 >> 2;
			output[j++] = _keyStr[enc1];

			if (i < 16)
			{
				chr2 = input[i++];
				enc2 = ((chr1 & 3) << 4) | (chr2 >> 4);
				output[j++] = _keyStr[enc2];
			}
			else
			{
				output[j++] = _keyStr[(chr1 & 3)<<4];
				break;
			}

			if (i < 16)
			{
				chr3 = input[i++];
				enc3 = ((chr2 & 15) << 2) | (chr3 >> 6);
				output[j++] = _keyStr[enc3];
			}
			else
			{
				output[j++] = _keyStr[(chr2 & 15)<<2];
				break;
			}

			enc4 = chr3 & 63;
			output[j++] = _keyStr[enc4];
		}

		return string((char*) output, j);
	}

	static string uuid_decode(string id)
	{
		static const char* _keyStr = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_=";
		unsigned char output[32];
		uint chr1, chr2, chr3;
		uint enc1, enc2, enc3, enc4;
		int i = 0;
		int j = 0;
		string input = id + "==";

		while (i < input.size())
		{
			enc1 = (std::strchr(_keyStr, input[i++]) - _keyStr);
			enc2 = (std::strchr(_keyStr, input[i++]) - _keyStr);
			enc3 = (std::strchr(_keyStr, input[i++]) - _keyStr);
			enc4 = (std::strchr(_keyStr, input[i++]) - _keyStr);

			chr1 = (enc1 << 2) | (enc2 >> 4);
			chr2 = ((enc2 & 15) << 4) | (enc3 >> 2);
			chr3 = ((enc3 & 3) << 6) | enc4;

			output[j++] = chr1;

			if (enc3 != 64)
			{
				output[j++] = chr2;
			}
			else break;
			if (enc4 != 64)
			{
				output[j++] = chr3;
			}
			else break;
		}
		return string((char*) output, j);
	}

	static string generate_uuid()
	{
		uuid_t uuid;
		uuid_generate_time(uuid);
		return Utils::pack_uuid(uuid);
	}

	static string generate_session_id()
	{
		uuid_t uuid;
		uuid_generate_time(uuid);
		string input((char*) uuid, 16);
		return uuid_encode(input);
	}

	static string generate_session_id2()
	{
		uuid_t uuid;
		char uuid_string[37];
		uuid_generate_time(uuid);
		string s((char*) uuid, 16);
		uuid_unparse(uuid, uuid_string);
		return string(uuid_string);
//		typedef base64_from_binary<transform_width<string::const_iterator, 6, 8> > base64_t;
//		string base64(base64_t(s.begin()), base64_t(s.end()));
//		return base64;
	}

	static bool normalize_string(string &str)
	{
		trim(str);
		if (str.empty()) return false;
		return true;
	}

	// only digital, character, - , _
	static bool normalize_code(string &str)
	{
		if (str.empty()) return false;

		// additional condition check

		// default
		return true;
	}

	static bool has_suffix(const std::string &str, const std::string &suffix)
	{
		if (str.size() <= suffix.size()) return false;
		string s = str.substr(str.size() - suffix.size(), suffix.size());
		return boost::iequals(s, suffix);
	}
};

}
#endif /* UTILS_H_ */
