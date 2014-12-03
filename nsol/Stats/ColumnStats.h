/**
 * @file    ColumnStats.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */
#ifndef __NSOL_COLUMN_STATS__
#define __NSOL_COLUMN_STATS__

#include "../Column.h"

namespace nsol
{

  /** \class ColumnStats
   *  \brief This class allows to compute stats for sections
   *
   *  Using this class instead of Column when constructing the
   *  hierarchy allows to call the method stats from base Column
   *  class and get the corresponding volume, surface and length.
   *
   * Example: @include examples/stats.cpp
   */
  class ColumnStats
    : public Column
  {

  public:

    typedef enum
    {
      // Volume
      DENDRITIC_VOLUME = 0,
      AXON_VOLUME,
      NEURITIC_VOLUME,
      SOMA_VOLUME,
      VOLUME,
      // Surface
      DENDRITIC_SURFACE,
      AXON_SURFACE,
      NEURITIC_SURFACE,
      SOMA_SURFACE,
      SURFACE,
      // Length
      DENDRITIC_LENGTH,
      AXON_LENGTH,
      NEURITIC_LENGTH,
      // Bifurcations
      DENDRITIC_BIFURCATIONS,
      AXON_BIFURCATIONS,
      NEURITIC_BIFURCATIONS,
      // This last one allows to know the number of stats
      COLUMN_NUM_STATS
    } TColumnStat;

    NSOL_API
    ColumnStats( const unsigned short id = 0 );


    NSOL_API
    float getStat( TColumnStat stat,
                   TAggregation miniColAgg = TAggregation::TOTAL,
                   TAggregation neuronAgg = TAggregation::TOTAL ) const;

    /**
     * Returns object as ColumnStats
     * @return pointer to ColumnStats object
     */
    NSOL_API
    virtual ColumnStats * stats( void );

  }; // class ColumnStats

} // namespace nsol

#endif // __NSOL_COLUMN_STATS__
