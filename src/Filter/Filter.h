#ifndef FILTER_H
#define FILTER_H

#include "ColorFilterMode.h"
#include "FilterColorEntry.h"
#include <QList>
#include <QRgb>

class QImage;

/// Class for filtering image to remove unimportant information.
class Filter
{
public:
  /// Single constructor.
  Filter();

  /// See if the two color values are close enough to be considered to be the same.
  bool colorCompare (QRgb rgb1,
                     QRgb rgb2) const;

  /// Filter the original image according to the specified filtering parameters.
  void filterImage (const QImage &imageOriginal,
                    QImage &imageFiltered,
                    ColorFilterMode colorFilterMode,
                    double low,
                    double high,
                    QRgb rgbBackground);

  /// Identify the margin color of the image, which is defined as the most common color in the four margins. For speed,
  /// only pixels in the four borders are examined, with the results from those borders safely representing the most
  /// common color of the entire margin areas.
  QRgb marginColor(const QImage *image) const;

  /// Return true if specified filtered pixel is on
  bool pixelFilteredIsOn (const QImage &image,
                          int x,
                          int y) const;

  /// Return pixel converted according to the current filter parameter, normalized to zero to one. Special
  /// case is -1 for a pixel that cannot be converted, like finding hue value for gray scale pixel
  double pixelToZeroToOneOrMinusOne (ColorFilterMode colorFilterMode,
                                     const QColor &pixel,
                                     QRgb rgbBackground) const;

  /// Return true if specified unfiltered pixel is on
  bool pixelUnfilteredIsOn (ColorFilterMode colorFilterMode,
                            const QColor &pixel,
                            QRgb rgbBackground,
                            double low0To1,
                            double high0To1) const;

  /// Inverse of pixelToZeroToOneOrMinusOne
  int zeroToOneToValue (ColorFilterMode colorFilterMode,
                        double s) const;

private:

  typedef QList<FilterColorEntry> ColorList;

  void mergePixelIntoColorCounts (QRgb pixel,
                                  ColorList &colorCounts) const;
};

#endif // FILTER_H
