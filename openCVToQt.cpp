#include <cstring>

#include "openCVToQt.hpp"

namespace
{
  template<typename T>
  inline QImage reference_mat_to_qimage(cv::Mat &mat, QImage::Format format)
  {
      return QImage((T*)(mat.data), mat.cols, mat.rows, mat.step, format);
  }  

  QImage copy_mat_to_qimage(cv::Mat const &mat, QImage::Format format)
  {
      QImage image(mat.cols, mat.rows, format);
      for (int i = 0; i != mat.rows; ++i){
          memcpy(image.scanLine(i), mat.ptr(i), image.bytesPerLine() );
      }

      return image;
  }
}

cv::Mat copy_qimage_to_mat_policy::start(QImage const &img, int format)
{
    cv::Mat mat(img.height(), img.width(), format);
    for(int i = 0; i != mat.rows; ++i){
        memcpy(mat.ptr(i), img.scanLine(i), img.bytesPerLine());
    }

    return mat;
}

QImage mat_to_qimage_cpy(cv::Mat &mat, int qimage_format)
{
    switch(mat.type()){

    case CV_8UC3 :
    {
        cv::cvtColor(mat, mat, CV_BGR2RGB);

        return copy_mat_to_qimage(mat, QImage::Format_RGB888);
    }

    case CV_8U :
    {
        return copy_mat_to_qimage(mat, QImage::Format_Indexed8);
    }

    case CV_8UC4 :
    {
        if(qimage_format == -1)
        {
            return copy_mat_to_qimage(mat, QImage::Format_ARGB32);
        }
        else
        {
            return copy_mat_to_qimage(mat, QImage::Format(qimage_format));
        }
    }

    default :
        return QImage();
    }
}

QImage mat_to_qimage_ref(cv::Mat &mat, int qimage_format)
{
    typedef unsigned char UC;    

    switch(mat.type()){

    case CV_8UC3 :
    {        
        cv::cvtColor(mat, mat, CV_BGR2RGB);

        return reference_mat_to_qimage<UC>(mat, QImage::Format_RGB888);
    }

    case CV_8U :
    {
        return reference_mat_to_qimage<UC>(mat, QImage::Format_Indexed8);
    }

    case CV_8UC4 :
    {        
        if(qimage_format == -1){
          return reference_mat_to_qimage<UC>(mat, QImage::Format_ARGB32);
        }
        else{
          return reference_mat_to_qimage<UC>(mat, QImage::Format(qimage_format));
        }
    }

    default :
        return QImage();
    }
}
