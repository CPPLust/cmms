/*****************************************************************//**
 * \file   TTime.h
 * \brief  
 * 
 * \author zcl1
 * \date   April 2025
 *********************************************************************/

#ifndef _BASE_TTIME_H_
#define _BASE_TTIME_H_
#include <stdint.h>
#include <string>


namespace cmms {

	class TTime {
	public:
		static int64_t NowMS();
		static int64_t Now();
		static int64_t Now(int& year, int& month, int& day, int& hour, int& minute, int& second);
		static std::string ISOTime();
	};




}

#endif // _BASE_TTIME_H_

