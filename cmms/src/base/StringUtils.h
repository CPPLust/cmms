#pragma once
#include <string>
#include <vector>

namespace cmms {
	class StringUtils
	{
	public:

		// �ַ���ǰ׺ƥ��
		static bool StartsWith(const std::string& s, const std::string& sub);

		// �ַ�����׺ƥ��
		static bool EndsWith(const std::string& s, const std::string& sub);

		// �����ļ�·�������ɲ�ͬ�����ļ�
		static std::string FilePath(const std::string& path);

		// ��������·����ȡ���ļ������ļ���׺
		static std::string FileNameExt(const std::string& path);

		// ���������ļ�·���з����ļ���
		static std::string FileName(const std::string& path);

		// �����ļ���׺
		static std::string Extension(const std::string& path);

		// �ַ����ָ�
		static std::vector<std::string> SplitString(const std::string& s, const std::string& delimiter);

		// ����״̬�����ַ����ָ�
		static std::vector<std::string> SplitStringWithFSM(const std::string& s, const char delimiter);
	};

}
