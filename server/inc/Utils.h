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

	static bool normalize_string(string &str)
	{
		trim(str);
		if (str.empty()) return false;
		return true;
	}
};

}
#endif /* UTILS_H_ */
