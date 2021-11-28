/*
 A template for a basic MSP external object with more explicit documentation
 
 See Readme of repository for build instructions.
 Create an Issue on the repository if anything is amiss or you have any suggestion
 - mhamilt Mar 2020
 */
#include "ext.h"
#include "ext_obex.h"
#include "z_dsp.h"
//------------------------------------------------------------------------------

/// void* to the complete new Max External class so that it can be used in the class methods
/// This will be set to t_class* in the main function and a global pointer to our class definition
/// @code t_class* c = class_new(...);
/// myExternClass = c;
static t_class* myExternClass;

//------------------------------------------------------------------------------
/// @struct MSPExternalObject
/// @abstract The MaxMSP object
/// @field externalMspObject Header for the MSP object
typedef struct _MSPExternalObject
{
    t_pxobject externalMspObject;
} MSPExternalObject;

//------------------------------------------------------------------------------
/// External Object Constructor: use this to setup any variables / properties of your DSP Struct or MSPExternalObject
/// Arguement list should be as long as the list of type arguments passed in the class_new call below.
/// @param s argument symbol
/// @param argc number of arguments
/// @param argv argument vector
/// @returns a void* to an instance of the MSPExternalObject
void* myExternalConstructor(t_symbol *s, long argc, t_atom *argv)
{
    //--------------------------------------------------------------------------
    MSPExternalObject* maxObjectPtr = (MSPExternalObject*)object_alloc(myExternClass);
    dsp_setup((t_pxobject*)maxObjectPtr, 1);
    //--------------------------------------------------------------------------
    outlet_new((t_object*)maxObjectPtr, "signal");
    return maxObjectPtr;
}

//------------------------------------------------------------------------------
/// @brief what happens when the object is deleted
void myExternDestructor(MSPExternalObject* maxObjectPtr)
{
    dsp_free((t_pxobject*)maxObjectPtr);
}

//------------------------------------------------------------------------------
#pragma mark DSP Loop
/// Main DSP process block, do your DSP here
/// @param maxObjectPtr
/// @param dsp64 can be used to interrogate the number of channels in each of your object’s inlets via the getnuminputchannels method. If your object has two inlets, here is how you can find out how many input channels each inlet has:
/// @param ins double pointer array to sample inlets
/// @param numins number of inputs
/// @param outs double pointer array to sample outlets
/// @param numouts number of outputs
/// @param sampleframes samples per channel
/// @param flags
/// @param userparam no idea
void mspExternalProcessBlock(MSPExternalObject* maxObjectPtr, t_object* dsp64,
                             double** ins, long numins, double** outs, long numouts,
                             long sampleframes, long flags, void* userparam)

{
    
}

//------------------------------------------------------------------------------

/// Audio DSP setup
/// @param maxObjectPtr object pointer
/// @param dsp64 can be used to interrogate the number of channels in each of your object’s inlets via the getnuminputchannels method. If your object has two inlets, here is how you can find out how many input channels each inlet has:
/// @param count array containing number of connections to an inlet with index [i]
/// @param samplerate
/// @param vectorsize
/// @param flags
void prepareToPlay(MSPExternalObject* maxObjectPtr, t_object* dsp64, short* count,
                   double samplerate, long vectorsize, long flags)
{
    object_method(dsp64,
                  gensym("dsp_add64"),
                  maxObjectPtr,
                  mspExternalProcessBlock,
                  0,
                  NULL);
}

//------------------------------------------------------------------------------
/// Bundle all class_addmethod calls into one function.
/// @param c max external class pointer
void coupleMethodsToExternal( t_class* c)
{
    class_addmethod(c, (method)prepareToPlay, "dsp64", A_CANT, 0);
}

//------------------------------------------------------------------------------
int C74_EXPORT main(void)
{
    t_class* c = class_new("max-external~",
                           (method)myExternalConstructor,
                           (method)myExternDestructor,
                           (short)sizeof(MSPExternalObject),
                           0L,
                           A_GIMME,
                           0);
    
    coupleMethodsToExternal(c);
    
    class_dspinit(c);
    class_register(CLASS_BOX, c);
    
    myExternClass = c;
    
    return 0;
}
//------------------------------------------------------------------------------

