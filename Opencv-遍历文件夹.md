# OpenCV遍历文件夹

```c++
/*
 * @Description: opencv中文件夹的操作
 * @Author: liuxiao
 * @Date: 2021-10-10 23:11:52
 */


#include <iostream>
#include <opencv2/core/utility.hpp>

/**
 * @Brief: 获取一个文件夹下所有的图片
 * @param folder: 文件夹路径
 * @return: 所哟图片(完整路径)
 */    
inline std::vector<cv::String> getAllJpgFiles(const cv::String& folder) {    
    std::vector<cv::String> allFiles;
    cv::glob(folder, allFiles, false);  // 不递归查找所有的图片
    //cv::glob(folder, allFiles, true); // 递归查找所有图片
    return allFiles;
}

/**
 * @Brief:          显示结果 
 * @param allFiles: 存放结果路径 
 * @return:         NULL
 */
inline void printAllFiles(const std::vector<cv::String>& allFiles) {
    for (auto &file : allFiles) {
        std::cout << file << std::endl;
    }
}

int main (int argc, char** argv) {
    cv::String folder = "E:\\repositories\\Environment-Setup\\imgs\\2_imgs";
    std::vector<cv::String> allFiles = getAllJpgFiles(folder);
    printAllFiles(allFiles);
    return 0;
}

/***********************************************************************************************
 void cv::glob(String pattern,                   文件夹路径
               std::vector< String > & result,   存放结构
               bool recursive = false)	         是否递归文件夹，默认不递归
 ***********************************************************************************************/

```

