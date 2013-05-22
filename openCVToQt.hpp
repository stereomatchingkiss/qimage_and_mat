#ifndef OPENCVTOQT_HPP
#define OPENCVTOQT_HPP

/*
 * collect some global functions to cross the gaps
 * between openCV and QImage
 */

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <QImage>

/*
 * copy QImage into cv::Mat
 */
struct copy_qimage_to_mat_policy
{
    static cv::Mat start(QImage const &img, int format);
};

/*
 * make Qimage and cv::Mat share the same buffer, the resource
 * of the cv::Mat must not deleted before the QImage finish
 * the jobs.
 */
struct reference_qimage_to_mat_policy
{
    static cv::Mat const start(QImage &img, int format)
    {
        return cv::Mat(img.height(), img.width(), format, img.bits(), img.bytesPerLine());
    }
};

/*
 * copy cv::Mat into QImage
 *
 *@param
 * qimage_format : specify type of the qimage, this parameter maybe useful
 * when the type of the qimage is ARGB, RGB32 and so on
 */
QImage mat_to_qimage_cpy(cv::Mat &mat, int qimage_format = -1);

/*
 * make Qimage and cv::Mat share the same buffer, the resource
 * of the cv::Mat must not deleted before the QImage finish
 * the jobs.
 *
 *@param
 * qimage_format : specify type of the qimage, this parameter maybe useful
 * when the type of the qimage is ARGB, RGB32 and so on
 */
QImage mat_to_qimage_ref(cv::Mat &mat, int qimage_format = -1);

/*
 * generic class for reducing duplicate codes
 */
template<typename T>
struct qimage_to_mat
{
    static cv::Mat run(QImage &img);
};

template<typename T>
cv::Mat qimage_to_mat<T>::run(QImage &img)
{    
    if(img.format() == QImage::Format_RGB888)
    {        
        cv::Mat result = T::start(img, CV_8UC3);
        cv::cvtColor(result, result, CV_BGR2RGB);

        return result;
    }

    if(img.format() == QImage::Format_Indexed8)
    {        
        return T::start(img, CV_8U);
    }

    if(img.format() == QImage::Format_RGB32 || img.format() == QImage::Format_ARGB32 ||
       img.format() == QImage::Format_ARGB32_Premultiplied)
    {                
        return T::start(img, CV_8UC4);
    }

    return cv::Mat();
}

inline cv::Mat qimage_to_mat_cpy(QImage &img)
{
    return qimage_to_mat<copy_qimage_to_mat_policy>::run(img);
}

inline cv::Mat qimage_to_mat_ref(QImage &img)
{
    return qimage_to_mat<reference_qimage_to_mat_policy>::run(img);
}

#endif // OPENCVTOQT_HPP
