//
////1 3 5 7 9
////    5
////
////1 3 7
////
////1 2 4 3 7
//
//#include <vector>
//#include <iostream>
//int main(int argc, char* argv[])
//{
//    std::vector<int> nums{ 1, 2, 3, 4, 5, 7 };
//    std::vector<int> nums2{ 3, 4, 6, 7, 8, 100 };
//
//
//
//    // new
//    std::vector<int> nums_all(0);
//
//    int i = 0, j = 0;
//
//    while (i < nums.size() && j < nums2.size())
//    {
//        if (nums[i] < nums2[j])
//        {
//            nums_all.push_back(nums[i]);
//            i++;
//        }
//        else // > =
//        {
//            nums_all.push_back(nums2[j]);
//            j++;
//        }
//    }
//    while (i < nums.size())
//    {
//        nums_all.push_back(nums[i]);
//        i++;
//    }
//
//    while (j < nums2.size())
//    {
//        nums_all.push_back(nums2[j]);
//        j++;
//    }
//
//
//    for (auto c : nums_all)
//        std::cout << c << " ";
//
//    std::cout << "\n";
//
//    if (!nums_all.empty() && nums_all.size() % 2 == 0)
//    {
//        std::cout << nums_all[nums_all.size() / 2] << "   " << nums_all[nums_all.size() / 2 + 1] << std::endl;
//        std::cout << ((nums_all[nums_all.size() / 2] > nums_all[nums_all.size() / 2 + 1]) ? (nums_all[nums_all.size() / 2 + 1]) : (nums_all[nums_all.size() / 2]));
//    }
//    if (!nums_all.empty() && nums_all.size() % 2 != 0)
//    {
//        std::cout << nums_all[nums_all.size() / 2 + 1] << std::endl;
//    }
//
//    /*   if (!nums.empty() && nums.size() % 2 == 0)
//      {
//          std::cout << nums[nums.size() / 2] << "   " << nums2[nums.size() / 2 + 1] << std::endl;
//          int a = nums[nums.size() / 2];
//          int b = nums2[nums.size() / 2 + 1];
//          if (a > b)
//          {
//              std::cout << b;
//          }
//          else
//          {
//              std::cout <<a;
//          }
//
//      }
//      if (!nums.empty() && nums.size() % 2 != 0)
//      {
//          std::cout << nums[nums.size() / 2 + 1]  << std::endl;
//      }*/
//
//    getchar();
//
//
//    return 0;
//}
//
//
