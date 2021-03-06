#ifndef FLAGS_H
#define FLAGS_H
//##############################################################################
//
// flags.h
//
//  - Preprocessor flags for lb3d_prime.

// set SAVE_MEMO to use the version of only ftemp without
// save the feq, f, in the momory.

#define SAVE_MEMO    0
//
// Set VERBOSITY_LEVEL to correspond to how deep into nested loops to
// print debug and related output.  Stuff will be printed down to
// loops nested VERBOSITY_LEVEL-1 deep. For example,
//
//   VERBOSITY_LEVEL 0 ==> Nothing is printed, even outside of loops.
//   VERBOSITY_LEVEL 1 ==> Only stuff outside of loops is printed.
//   VERBOSITY_LEVEL 2 ==> Stuff inside the first level of loops is printed.
//   VERBOSITY_LEVEL 3 ==> Stuff inside the second level of loops is printed.
//
// Flag: VERBOSITY_LEVEL
#define VERBOSITY_LEVEL 1

// If SAY_HI is on, some routines will display "hi" and "bye" messages
// to stdout.
// Flag: SAY_HI
#define SAY_HI 0

// INTEGER_IC_BOUND forces x0, y0, z0, r0 and x1, x2, y1, y2, z1, z2 to be
// integer values.  Since the lattice can't resolve shapes with non-integer
// dimensions, using integers makes sense.  This flag is particularly
// important when setting LX or LY to unity for a 2D simulation
#define INTEGER_IC_BOUND 1

// NUM_FLUID_COMPONENTS specifies the number of fluid components.
// Flag: NUM_FLUID_COMPONENTS
#define NUM_FLUID_COMPONENTS 2

//if it is SPONGE, the total computational domain firstly initiallized
//as randomly distributed fluid1 and fluid2 , however, the upper and
//lower computational domain controled by lattice->param.z1 (<), and
//lattice->param.z2 (>) will be initiallized again as uniform fluid1 (Wetting)
#define SPONGE (0 && NUM_FLUID_COMPONENTS==2)

// If NUM_FLUID_COMPONENTS is 2, the second component can be the sigma
// component for solute (or thermal) transport as in Inamuro & Yoshino
// by turning on INAMURO_SIGMA_COMPONENT .
// Flag: INAMURO_SIGMA_COMPONENT
#define INAMURO_SIGMA_COMPONENT ( 0 && NUM_FLUID_COMPONENTS==2)

// Toggle Zhang & Chen energy transport method, PRE 67, 0066711 (2003).
// Supposed to give thermodynamic consistency unlike old Shan & Chen method.
// And supports general equation of state P = P(rho,T).
// Utilizes the Inamuro component for evolution of the energy transport
// equation.  Employs modified compute_phase_force routine to compute
// body force term representing non-local interaction potential U among
// particles.
// Flag: ZHANG_AND_CHEN_ENERGY_TRANSPORT
#define ZHANG_AND_CHEN_ENERGY_TRANSPORT ( 0 && (INAMURO_SIGMA_COMPONENT))

// Simulate POROUS_MEDIA via a solid density parameter
// c.f., Walsh, Stuart D. C. and Burwinkle, Holly and Saar, Martin
// O., A new partial-bounceback lattice-Boltzmann method for fluid
// flow through heterogeneous media, COMPUTERS & GEOSCIENCES, 2009,
// 35, 6, 1186-1193, JUN, ISI:000266544700013
// Flag: POROUS_MEDIA
#define POROUS_MEDIA 0

// When there are two (or more) fluid components, a single velocity is
// sometimes (always?) used to compute the equilibrium distribution
// function.  This single velocity will be called ueq, and the
// STORE_UEQ flag will toggle its use.
// Flag: STORE_UEQ
#define STORE_UEQ ( 1 && (  (NUM_FLUID_COMPONENTS)==2 \
                          &&!((INAMURO_SIGMA_COMPONENT))))

// If DO_NOT_STORE_SOLIDS is on, then only the nodes necessary to flow are
// stored.  In this case, extra storage is needed for geometry information
// (e.g. node neighbors).  If the ratio of fluid nodes to solid nodes is
// small (<~.7), this results in lower storage requirements.
// Flag: DO_NOT_STORE_SOLIDS
#define DO_NOT_STORE_SOLIDS 0
// If COMPUTE_ON_SOLIDS is on, macroscopic variables and feq will be computed
// on solid nodes, even though they are not conceptually meaningful there.
// This can be helpful for debugging purposes.
#define COMPUTE_ON_SOLIDS 0
// NON_LOCAL_FORCES toggles any mechanisms for computing and storing
// non-local (interaction) forces.
// Flag: NON_LOCAL_FORCES
#define NON_LOCAL_FORCES ( 1 && !(INAMURO_SIGMA_COMPONENT&&!ZHANG_AND_CHEN_ENERGY_TRANSPORT))

// The phase force weighting factors:
//   WM = weights in the direction of major axes
//   WD = weights in the direction of diagonals
// According to Raskinmaki, it should be WM=2 and WD=1.
// According to Chen (via correspondence) it should be WM=4 and WD=1.
// According to Sukop and Thorne, it should be WM=1/9 and WD=1/36.
// The corresonding G values (a.k.a. big_V0, as in params.in) for the usual
// equation of state that we like are -5, -10/3, and -120, respectively.
// Flag: WM
//#define WM 2.
#define WM 1./18.
// Flag: WD
//#define WD 1.
#define WD 1./36.

#define Q 19

#define N2X(N,NX,NY,NZ) (N)%(NX)
#define N2Y(N,NX,NY,NZ) (int)floor((double)((N)%((NX)*(NY)))/(double)(NX))
#define N2Z(N,NX,NY,NZ) (int)floor((double)(N)/(double)((NX)*(NY)))
#define XYZ2N(X,Y,Z,NX,NY) ( (Z)*(NX)*(NY) + (Y)*(NX) + (X))

// Toggle manage_body_force call at beginning of time loop for
// gradually increasing/decreasing gravity.
// Flag: MANAGE_BODY_FORCE
#define MANAGE_BODY_FORCE 0

// Toggle break through curve (BTC) mechanism for sigma component.
// Flag: STORE_BTC
#define STORE_BTC ( 1 && INAMURO_SIGMA_COMPONENT)

//
// Toggle DETERMINE_FLOW_DIRECTION to attempt to determine the direction of
// flow.
//
// Assigns FlowDir = { 0, 1, 2} = { indeterminate, vertical, horizontal}
//
// NOTE: This determination informs the breakthrough curve mechanism which
// should be used in a simple situation with either pressure/velocity
// boundaries driving the flow in one direction or gravity driving the flow
// in one direction.  If the direction of flow cannot be determined, FlowDir
// will be set to indeterminate (=0) and a BTC will not be stored.
//
// NOTE: This determination also informs the sigma slip boundary which
// should only be used in the simple situation of flow through a channel
// where the geometry is trivial and the direction of flow is obvious.
//
// Flag: DETERMINE_FLOW_DIRECTION
#define DETERMINE_FLOW_DIRECTION 0

// Toggle mechanism to initialize domain with ux_in, uy_in or uz_in. This is
// useful for setting a velocity in a periodic domain without using fluid
// boundary conditions.
// Flag: INITIALIZE_WITH_UX_IN
#define INITIALIZE_WITH_UX_IN   0
// Flag: INITIALIZE_WITH_UY_IN
#define INITIALIZE_WITH_UY_IN   0
// Flag: INITIALIZE_WITH_UZ_IN
#define INITIALIZE_WITH_UZ_IN   0

// Write .raw files for viewing with imagej, volsuite, 3dview, etc...
// Flag: WRITE_MACRO_VAR_RAW_FILES
#define WRITE_MACRO_VAR_RAW_FILES 1

#define WRITE_PLOT_FILE 0
//Write .txt file with one-dimensional array of vmag values precalculated
//to avoid memory output issues that arise with post-processing of larger
//domains.
//Flag: WRITE_VMAG
#define WRITE_VMAG 0

// Dumping the density and velocity data to files can be time consuming and
// take up a lot of disk space.  If all that is needed is the BMP files, then
// turn WRITE_MACRO_VAR_DAT_FILES off to save time and space.
// Flag: WRITE_MACRO_VAR_DAT_FILES
#define WRITE_MACRO_VAR_DAT_FILES 1

// Usually the density and velocity are written only for the active nodes
// and in a way designed for post-processing.  Additional files with the
// variables written in a readable grid of all lattice nodes will be
// generated when WRITE_RHO_AND_U_TO_TXT is on.  This is done in an
// inefficient way and is intended only for debugging purposes on tiny
// lattices.  Note that if WRITE_MACRO_VAR_DAT_FILES is off, this flag
// has no effect.
// Flag: WRITE_RHO_AND_U_TO_TXT
#define WRITE_RHO_AND_U_TO_TXT 0

// WRITE_PDF_DAT_FILES is analogous to WRITE_MACRO_VAR_DAT_FILES.
// Flag: WRITE_PDF_DAT_FILES
#define WRITE_PDF_DAT_FILES 0

// WRITE_PDF_TO_TXT is analogous to WRITE_RHO_AND_U_TO_TXT.
// Flag: WRITE_PDF_TO_TXT
#define WRITE_PDF_TO_TXT 0

// Value used to represent an INACTIVE_NODE .  This is used in the list
// of neighbors ( struct node_struct::nn).
// Flag: INACTIVE_NODE
#define INACTIVE_NODE -1

// Negative densities (f_a) generally signify impending doom.  The code
// will die "gracefully" when this happens if PUKE_NEGATIVE_DENSITIES is on.
// Might want to turn this off to boost performance on big, long runs that
// are expected to survive without such instabilities.
// Flag: PUKE_NEGATIVE_DENSITIES
#define PUKE_NEGATIVE_DENSITIES 0

// Turn one of these on for coloring of the solids in bmp files.
// Flag: SOLID_COLOR_IS_CHECKERBOARD
#define SOLID_COLOR_IS_CHECKERBOARD 0
// Flag: SOLID_COLOR_IS_BLACK
#define SOLID_COLOR_IS_BLACK        1

// Flag: DELAY
#define DELAY    0
// Flag: END_GRAV
#define END_GRAV 2000

// A single white pixel will be placed in at the (0,0) lattice node if
// MARK_ORIGIN_FOR_REFERENCE is turned on.  This is good for assisting with the
// problem of tracking orientation of the results between regimes (e.g. C, BMP,
// Matlab...).
// Flag: MARK_ORIGIN_FOR_REFERENCE
#define MARK_ORIGIN_FOR_REFERENCE 0

// Flag: PERTURBATIONS
#define PERTURBATIONS 0

#endif /* FLAGS_H */
