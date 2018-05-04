// --------------------------------------------------------------------------------------------------------------------
//
//! \file PusherFactory.h
//
//! \brief Class PusherFactory that manage the pusher association to the species.
//
// --------------------------------------------------------------------------------------------------------------------

#ifndef PUSHERFACTORY_H
#define PUSHERFACTORY_H

#include "Pusher.h"
#include "PusherBoris.h"
#include "PusherPonderomotiveBoris.h"
#include "PusherPonderomotivePositionBoris.h"
#include "PusherVay.h"
#include "PusherBorisNR.h"
#include "PusherRRLL.h"
#include "PusherHigueraCary.h"
#include "PusherPhoton.h"

#ifdef _VECTO
#include "PusherBorisV.h"
#include "PusherPonderomotiveBorisV.h"
#endif

#include "Params.h"
#include "Species.h"

#include "Tools.h"

//  --------------------------------------------------------------------------------------------------------------------
//! Class PusherFactory
//
//! \brief Class PusherFactory that manage the pusher association to the species.
//  --------------------------------------------------------------------------------------------------------------------
class PusherFactory {
public:
    //  --------------------------------------------------------------------------------------------------------------------
    //! Create appropriate pusher for the species ispec
    //! \param ispec SpeciesId
    //! \param params Parameters
    //  --------------------------------------------------------------------------------------------------------------------
    static Pusher* create(Params& params, Species * species) {
        Pusher* Push = NULL;

        // Particle of matter
        if (species->mass > 0) {
            // assign the correct Pusher to Push
            if ( species->pusher == "boris")
            {
                if (!species->vectorized_operators)
                    Push = new PusherBoris( params, species );
#ifdef _VECTO
                else
                    Push = new PusherBorisV( params, species );
#endif
            }
            else if ( species->pusher == "ponderomotive_boris" )
            {
                if (!species->vectorized_operators)
                    Push = new PusherPonderomotiveBoris( params, species );
#ifdef _VECTO
                else
                    ERROR("Ponderomotive pusher not yet implemented for vectorised version");
                    //Push = new PusherPonderomotiveBorisV( params, species );
#endif
            }
            else if ( species->pusher == "borisnr" )
            {
                Push = new PusherBorisNR( params, species );
            }
            /*else if ( species->pusher == "rrll" )
            {
                Push = new PusherRRLL( params, species );
            }*/
            else if ( species->pusher == "vay" )
            {
                Push = new PusherVay( params, species );
            }
            else if ( species->pusher == "higueracary" )
            {
                Push = new PusherHigueraCary( params, species );
            }
            else {
                ERROR( "For species " << species->name
                                      << ": unknown pusher `"
                                      << species->pusher << "`");
            }
        }
        // Photon
        else if (species->mass == 0)
        {
            if ( species->pusher == "norm")
            {
                Push = new PusherPhoton( params, species );
            }
            else {
                ERROR( "For photon species " << species->name
                                      << ": unknown pusher `"
                                      << species->pusher << "`");
            }
        }

        if (species->ponderomotive_dynamics){
            if (species->pusher != "ponderomotive_boris"){
                ERROR( "For species " << species->name << " the flag ponderomotive_dynamics is True - the only pusher available to interact with the envelope is ponderomotive_boris");
                }
            }
        return Push;
    }

    static Pusher* create_ponderomotive_position_updater(Params& params, Species * species) {
        Pusher* Push_ponderomotive_position = NULL;

        // Particle of matter
        if (species->mass > 0) {
            // assign the correct Pusher to Push_ponderomotive_position
            if ( species->pusher == "ponderomotive_boris" )
            {
                if (!species->vectorized_operators)
                    Push_ponderomotive_position = new PusherPonderomotivePositionBoris( params, species );
#ifdef _VECTO
                else
                    ERROR("Ponderomotive pusher not yet implemented for vectorised version");
                    //Push = new PusherPonderomotiveBorisV( params, species );
#endif
            }
          
            else {
                ERROR( "For species " << species->name
                                      << ": unknown pusher `"
                                      << species->pusher << "`");
            }
        } else {ERROR("Ponderomotive pusher is not a valid choice for photons"); }
        return Push_ponderomotive_position;
    }

};

#endif
