//
//#include <string>
//#include <iostream>
//
//void removeChars(std::string& str, const std::string& remove) {
//	size_t write_pos = 0; // 初始化写指针，记录有效字符的位置
//
//	// 遍历原始字符串的每个字符
//	for (char c : str) {
//		// 检查当前字符是否需要移除
//		if (remove.find(c) == std::string::npos) {  // 如果在移除列表中找到该字符
//			str[write_pos++] = c;  // 保留字符并移动写指针
//		}
//		// 若需要移除则跳过（不执行任何操作）
//	}
//
//	str.resize(write_pos);  // 截断字符串到有效长度
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
