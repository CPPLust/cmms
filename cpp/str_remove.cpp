//
//#include <string>
//#include <iostream>
//
//void removeChars(std::string& str, const std::string& remove) {
//	size_t write_pos = 0; // ��ʼ��дָ�룬��¼��Ч�ַ���λ��
//
//	// ����ԭʼ�ַ�����ÿ���ַ�
//	for (char c : str) {
//		// ��鵱ǰ�ַ��Ƿ���Ҫ�Ƴ�
//		if (remove.find(c) == std::string::npos) {  // ������Ƴ��б����ҵ����ַ�
//			str[write_pos++] = c;  // �����ַ����ƶ�дָ��
//		}
//		// ����Ҫ�Ƴ�����������ִ���κβ�����
//	}
//
//	str.resize(write_pos);  // �ض��ַ�������Ч����
//}
//
//int main(int argc, char* argv[])
//{
//	std::string src = "hello world";
//	std::string remove = "ow";
//	removeChars(src, remove);
//
//	std::cout << "remove src " << src << std::endl;
//
//	getchar();
//	return 0;
//}
