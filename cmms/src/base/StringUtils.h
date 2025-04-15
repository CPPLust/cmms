#pragma once
#include <string>
#include <vector>

namespace cmms {
	class StringUtils
	{
	public:

		// 字符串前缀匹配
		static bool StartsWith(const std::string& s, const std::string& sub);

		// 字符串后缀匹配
		static bool EndsWith(const std::string& s, const std::string& sub);

		// 返回文件路径，生成不同名的文件
		static std::string FilePath(const std::string& path);

		// 从完整的路径中取出文件名和文件后缀
		static std::string FileNameExt(const std::string& path);

		// 从完整的文件路径中返回文件名
		static std::string FileName(const std::string& path);

		// 返回文件后缀
		static std::string Extension(const std::string& path);

		// 字符串分割
		static std::vector<std::string> SplitString(const std::string& s, const std::string& delimiter);

		// 有限状态机的字符串分割
		static std::vector<std::string> SplitStringWithFSM(const std::string& s, const char delimiter);
	};

}
