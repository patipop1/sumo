#ifndef MSAPPROACHINGVEHICLESSTATES_H
#define MSAPPROACHINGVEHICLESSTATES_H

/**
 * @file   MSApproachingVehiclesStates.h
 * @author Christian Roessel
 * @date   Started Thu Oct 16 14:45:00 2003
 * @version $Id$
 * @brief  
 * 
 * 
 */

/* Copyright (C) 2003 by German Aerospace Center (http://www.dlr.de) */

//---------------------------------------------------------------------------//
//
//   This program is free software; you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation; either version 2 of the License, or
//   (at your option) any later version.
//
//---------------------------------------------------------------------------//

#include "MSDetectorContainer.h"
#include "MSUnit.h"
#include "MS_E2_ZS_Collector.h"
#include <string>
#include <vector>
#include <iterator>

class MSApproachingVehiclesStates 
{
    friend class MS_E2_ZS_Collector; // only MS_E2_ZS_Collector has
                                     // access to ctor
public:
    class VehicleState
    {
    public:
        VehicleState( MSUnit::Cells gap2DetectorEnd,
                      MSUnit::CellsPerStep speed ) 
            : gap2DetectorEndM( MSUnit::getInstance()->getMeters(
                                    gap2DetectorEnd ) ),
              speedM( MSUnit::getInstance()->getMetersPerSecond(
                          speed ) )
            {}

        MSUnit::Meters getGap2DetectorEnd( void ) const 
            {
                return gap2DetectorEndM;
            }

        MSUnit::MetersPerSecond getSpeed( void ) const
            {
                return speedM;
            }
        
    private:
        MSUnit::Meters gap2DetectorEndM;
        MSUnit::MetersPerSecond speedM;
    };

    typedef std::vector< VehicleState > DetectorAggregate;
    
protected:
    typedef DetectorContainer::Vehicles Container;
    typedef Container::InnerCont VehicleCont;
    
    MSApproachingVehiclesStates( MSUnit::Meters detectorEndPos,
                                 const Container& vehicleCont ) 
        : detectorEndPosM( MSUnit::getInstance()->getCells( detectorEndPos ) ),
          containerM( vehicleCont.containerM ),
          statesM()
        {}

    virtual ~MSApproachingVehiclesStates( void )
        {
            statesM.clear();
        }
    
    const DetectorAggregate& getDetectorAggregate( unsigned nApproachingVeh )
        {
            statesM.clear();

            VehicleCont::const_iterator vehIt = containerM.begin();
            if ( (*vehIt)->pos() > detectorEndPosM ) {
                ++vehIt;
            }
            unsigned nValidVehicles = std::distance( vehIt, containerM.end() );
            if ( nValidVehicles < nApproachingVeh ) {
                nApproachingVeh = nValidVehicles;
            }
            
            for ( unsigned index = 0; index < nApproachingVeh; ++index ) {
                statesM.push_back(
                    VehicleState( detectorEndPosM - (*vehIt)->pos(),
                                  (*vehIt)->speed() ) );
            }
            return statesM;
        }
    
    static std::string getDetectorName( void )
        {
            return "approachingVehiclesStates";
        }
    
private:
    MSUnit::Cells detectorEndPosM;
    const VehicleCont& containerM;
    DetectorAggregate statesM;
};

#endif // MSAPPROACHINGVEHICLESSTATES_H

// Local Variables:
// mode:C++
// End:
