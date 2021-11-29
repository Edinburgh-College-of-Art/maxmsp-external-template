/*
 A template for a basic max external object with more explicit documentation
 
 See Readme of repository for build instructions.
 Create an Issue on the repository if anything is amiss or you have any suggestion
 - mhamilt Mar 2020
 */
#include "ext.h"
#include "ext_obex.h"
//------------------------------------------------------------------------------

/// void* to the complete new Max External class so that it can be used in the class methods
/// This will be set to t_class* in the main function
/// @code t_class* c = class_new(...);
/// myExternClass = c;
static t_class* myExternClass;

//------------------------------------------------------------------------------
/** @struct
 The MaxMSP object
 */
typedef struct _MaxExternalObject
{
    t_object externalMaxObject;
} MaxExternalObject;
//------------------------------------------------------------------------------
/// External Object Constructor: use this to setup any variables / properties of your DSP Struct or MaxExternalObject
/// Arguement list should be as long as the list of type arguments passed in the class_new call below.
/// @param arg1 first argument to object: should match type given in class_new(...)
/// @returns a void* to an instance of the MaxExternalObject
void* myExternalConstructor(t_symbol *s, long argc, t_atom *argv)
{
    //--------------------------------------------------------------------------
    MaxExternalObject* maxObjectPtr = (MaxExternalObject*)object_alloc(myExternClass);
    //--------------------------------------------------------------------------
    return maxObjectPtr;
}

//------------------------------------------------------------------------------
/// @brief what happens when the object is deleted
void myExternDestructor(MaxExternalObject* maxObjectPtr)
{    
}
//------------------------------------------------------------------------------

/// @brief This is the function called by Max when the cursor is over an inlet or outlet.
/// @param maxObjectPtr object pointer
/// @param jbox pointer to the object box in the patcher. Use jbox methods to query
/// @param message either inlet  1 or outlet 2
/// @param arg inlet / outlet index
/// @param dstString pointer to destination: limited to 60 chars.
void inletAssistant(MaxExternalObject* maxObjectPtr,
                    void *jbox,
                    long message,
                    long arg,
                    char *dstString)
{
}

//------------------------------------------------------------------------------

/// This gets called when we receive a bang
/// @param maxObjectPtr object pointer
void onBang(MaxExternalObject* maxObjectPtr)
{
}

/// This gets called when we receive a float
/// @param maxObjectPtr object pointer
/// @param floatIn 
void onFloat(MaxExternalObject* maxObjectPtr, double floatIn)
{
}
//------------------------------------------------------------------------------

/// This gets called when a list is sent to the object
/// @param maxObjectPtr object pointer
/// @param s message selector contains the text of a message and a pointer to the message object
/// @param argc number of atoms in the argv array
/// @param argv array of atoms holding the arguments.
void onList(MaxExternalObject* maxObjectPtr,
            t_symbol *s,
            short argc,
            t_atom *argv)
{
}

//------------------------------------------------------------------------------

void onPrintMessage(MaxExternalObject* x)
{    
}

//------------------------------------------------------------------------------

/// If any message is recieved an we have not already dealt with it
/// @param maxObjectPtr object pointer
/// @param s message selector contains the text of a message and a pointer to the message object
/// @param argc number of atoms in the argv array
/// @param argv array of atoms holding the arguments.
void onAnyMessage(MaxExternalObject* maxObjectPtr, t_symbol *s, long argc, t_atom *argv)
{
}

//------------------------------------------------------------------------------
/// Bundle all class_addmethod calls into one function.
/// @param c max external class pointer
void coupleMethodsToExternal( t_class* c)
{
    class_addmethod(c, (method)onBang, "bang", 0);
    class_addmethod(c, (method)onList, "list", A_GIMME, 0);
    class_addmethod(c, (method)onFloat, "float", A_FLOAT, 0);
    class_addmethod(c, (method)inletAssistant,"assist", A_CANT,0);
    class_addmethod(c, (method)onPrintMessage, "print", 0);
    class_addmethod(c, (method)onAnyMessage, "anything", A_GIMME, 0);    
}
//------------------------------------------------------------------------------
int C74_EXPORT main(void)
{
    t_class* c = class_new("max-external",
                           (method)myExternalConstructor,
                           (method)myExternDestructor,
                           (short)sizeof(MaxExternalObject),
                           0L,
                           A_GIMME,
                           0);
    
    coupleMethodsToExternal(c);
        
    class_register(CLASS_BOX, c);
    
    myExternClass = c;
    
    return 0;
}
//------------------------------------------------------------------------------

