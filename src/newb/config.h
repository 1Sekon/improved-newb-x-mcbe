#ifndef NL_CONFIG_H
#define NL_CONFIG_H

// line 3 reserved

/*
  EDITING CONFIG:

  > TOGGLES
  if [toggle] is mentioned, then
  options can be commented to disable (by adding/removing '//')
  eg: #define PLANTS_WAVE    -> this is ON
      //#define PLANTS_WAVE  -> this is OFF

  > COLOR VALUES
  color format: vec3(<red>,<green>,<blue>)
  1.0 means 100%, 0.0 means 0%
  eg. vec3(1.0,1.0,0.0) = yellow

  > VALUES
  values must be decimal
  eg. 32 is wrong, 32.0 is correct

  > TYPES
  should be integer. options to choose will be mentioned there
  eg: #define NL_FOG_TYPE 2

  BUILD THE SHADER AFTER EACH EDIT
  
NLC = NewbLegacyCustom
  
*/

/* -------- CONFIG STARTS HERE ----------- */

/* Color correction */

#define NL_TONEMAP_TYPE 4   // 1:Exponential, 2:Reinhard, 3:Extended Reinhard, 4:ACES
#define NL_CONSTRAST 0.831   // 0.3 low ~ 2.0 high
#define NL_EXPOSURE 1.953   // [toggle] 0.5 dark ~ 3.0 bright //1.85
#define NL_SATURATION 1.54 // [toggle] 0.0 grayscale ~ 4.0 super saturated
//#define NL_TINT vec3(1.1,1.1,1.0) // [toggle] color overlay

/* Terrain lighting */
#define NL_SUN_INTENSITY 2.97   // 0.5 weak ~ 5.0 bright
#define NL_TORCH_INTENSITY 0.6  // 0.5 weak ~ 3.0 bright
#define NL_NIGHT_BRIGHTNESS 0.0 // 0.0 dark ~ 2.0 bright 0.65
#define NL_CAVE_BRIGHTNESS  0.2 // 0.0 dark ~ 2.0 bright
#define NL_SHADOW_INTENSITY 0.8 // 0.0 no shadow ~ 1.0 strong shadow
#define NL_BLINKING_TORCH     // [toggle] flickering light
//#define NL_CLOUD_SHADOW     // [toggle] cloud shadow (simple clouds only)

/* Sun/moon light color on terrain */
#define NL_MORNING_SUN_COL vec3(1.11,0.45,0.14)
#define NL_NOON_SUN_COL    vec3(1.167,0.77,0.6)
#define NL_NIGHT_SUN_COL   vec3(0.34,0.5,0.75)

/* Ambient light on terrain (light that is added everywhere) */
#define NL_NETHER_AMBIENT vec3(0.67,0.6,0.4)
#define NL_END_AMBIENT vec3(0.32,0.15,0.32)+0.16

/* Torch colors */
#define NL_OVERWORLD_TORCH_COL  vec3(0.85,0.52,0.41)
#define NL_UNDERWATER_TORCH_COL vec3(0.3,1.0,0.6)
#define NL_NETHER_TORCH_COL     vec3(0.48,0.42,0.3)
#define NL_END_TORCH_COL        vec3(1.0,0.52,0.18)

/* Fog */
#define NL_FOG_TYPE 2        // 0:no fog, 1:vanilla, 2:smoother vanilla

// 0.0 no mist ~ 1.0 misty
#define NLC_MIST_DENS_NOON 0.25
#define NLC_MIST_DENS_DAWN 0.27
#define NLC_MIST_DENS_NIGHT 1.5
#define NLC_MIST_DENS_END 0.3

/* Sky colors - zenith=top, horizon=bottom */
#define NL_DAY_ZENITH_COL    vec3(0.151,0.322,0.992)*1.1
#define NL_DAY_HORIZON_COL   vec3(0.53,0.73,0.93)+0.2*2.0

#define NL_NIGHT_ZENITH_COL  vec3(0.058,0.075,0.09)*0.67
#define NL_NIGHT_HORIZON_COL vec3(0.058,0.075,0.09)*2.3

#define NL_RAIN_ZENITH_COL   vec3(0.57,0.68,0.86)
#define NL_RAIN_HORIZON_COL  vec3(0.68,0.77,1.0)

#define NL_END_ZENITH_COL    vec3(0.02,0.007,0.04)
#define NL_END_HORIZON_COL   vec3(0.25,0.15,0.4)

//#define NL_DAWN_HORIZON_COL  vec3(1.0,0.55,0.33)
#define NL_DAWN_HORIZON_COL  vec3(0.77,0.512,0.592)*0.9
//#define NL_DAWN_ZENITH_COL   vec3(0.13,0.14,0.2)*1.4
#define NL_DAWN_ZENITH_COL	 vec3(0.27,0.312,0.492)*0.8
#define NL_DAWN_EDGE_COL     vec3(1.0,0.6,0.3)//vec3(1.2,0.514,0.231)

/* Rainbow */
//#define NL_RAINBOW         // [toggle] enable rainbow in sky
#define NL_RAINBOW_CLEAR 0.0 // 0.3 subtle ~ 1.7 bright during clear
#define NL_RAINBOW_RAIN 0.6  // 0.5 subtle ~ 2.0 bright during rain

/* Ore glow intensity */
#define NL_GLOW_TEX 2.3  // 0.4 weak ~ 8.0 bright
#define NL_GLOW_SHIMMER  // [toggle] shimmer effect
//#define NL_GLOW_LEAK 0.7 // [toggle] 0.08 subtle ~ 1.0 100% brightness of NL_GLOW_TEX

/* Waving */
#define NL_PLANTS_WAVE 0.07    // [toggle] 0.02 gentle ~ 0.4 violent
#define NL_LANTERN_WAVE 0.15   // [toggle] 0.05 subtle ~ 0.4 large swing
#define NL_WAVE_SPEED 1.5      // 0.5 slow wave ~ 5.0 very fast wave
//#define NL_EXTRA_PLANTS_WAVE // [toggle] !dont use! wave using texture coords (1.20.40 vanilla)

/* Water */
#define NL_WATER_TRANSPARENCY 0.34 // 0.0 transparent ~ 1.0 normal
#define NL_WATER_BUMP 0.15        // 0.001 plain ~ 0.2 bumpy water
#define NL_WATER_TEX_OPACITY 0.3  // 0.0 plain water ~ 1.0 vanilla water texture
#define NL_WATER_WAVE             // [toggle] wave effect
#define NL_WATER_FOG_FADE         // [toggle] fog fade for water
#define NL_WATER_REFLECTION // [toggle] simple clouds/aurora reflection
#define NL_WATER_TINT vec3(0.14,0.34,0.6)

/* Underwater */
#define NL_UNDERWATER_BRIGHTNESS 0.3 // 0.0 dark ~ 3.0 bright
#define NL_CAUSTIC_INTENSITY 2.5     // 0.5 weak ~ 5.0 bright
#define NL_UNDERWATER_WAVE 0.1       // [toggle] 0.02 subtle ~ 0.6 trippy
#define NL_UNDERWATER_STREAKS 1.9    // [toggle] 0.8 subtle - 2.0 bright streaks from top
#define NL_UNDERWATER_TINT vec3(0.3,0.5,0.6)

/* Cloud type */
#define NL_CLOUD_TYPE 2 // 0:vanilla, 1:soft, 2:rounded, 3:fbm
#define NLZ_CLOUD3_SPEED 0.15
/* Vanilla cloud settings - make sure to remove clouds.png when using this */
#define NL_CLOUD0_THICKNESS 2.0      // 0.5 slim ~ 8.0 fat
#define NL_CLOUD0_RAIN_THICKNESS 4.0 // 0.5 slim ~ 8.0 fat

/* Soft cloud settings */
#define NL_CLOUD1_SCALE_XZ vec2(0.02, 0.025) // 0.003 large ~ 0.2 tiny
#define NL_CLOUD1_DEPTH 2.5                // 0.0 no bump ~ 10.0 large bumps
#define NL_CLOUD1_SPEED 0.08               // 0.0 static ~ 0.4 fast moving
#define NL_CLOUD1_DENSITY 0.22             // 0.1 less clouds ~ 0.8 more clouds
#define NL_CLOUD1_OPACITY 0.85              // 0.0 invisible ~ 1.0 opaque

/* Rounded cloud Settings */

#define NL_CLOUD2_THICKNESS 2.1      // 0.5 slim ~ 5.0 fat
#define NL_CLOUD2_RAIN_THICKNESS 2.2 // 0.5 slim ~ 5.0 fat
#define NL_CLOUD2_STEPS 5          // 3 low quality ~ 16 high quality (Lag)
#define NL_CLOUD2_SCALE 0.035        // 0.003 large ~ 0.3 tiny
#define NL_CLOUD2_SHAPE 0.65	         // 0.0 round ~ 1.0 box
#define NL_CLOUD2_DENSITY 5.0        // 1.0 blurry ~ 100.0 sharp
#define NL_CLOUD2_VELOCIY 2.5       // 0.0 static ~ 4.0 very fast
// #define NL_CLOUD2_MULTILAYER       // [toggle] extra cloud layer
#define NLC_CLOUD2_AMOUNT 0.007
#define NLC_CLOUD2_OPACITY 0.95
#define NLC_DAY_CLOUD2_TINT   vec3(1.34,1.3,1.3)
#define NLC_DAWN_CLOUD2_TINT  vec3(0.5,0.4,0.25)
#define NLC_NIGHT_CLOUD2_TINT vec3(0.001, 0.002, 0.004)*10.0
#define NLC_RAIN_CLOUD2_TINT  vec3(0.62, 0.6, 0.6)

/* Aurora settings */
#define NL_AURORA 2.6           // [toggle] 0.4 dim ~ 4.0 very bright
#define NL_AURORA_VELOCITY 0.4 // 0.0 static ~ 0.3 very fast
#define NL_AURORA_SCALE 0.9    // 0.002 large ~ 0.4 tiny
#define NL_AURORA_WIDTH 0.08    // 0.04 thin line ~ 0.4 thick lines
#define NL_AURORA_COL2  vec3(0.12,0.45,0.34)
#define NL_AURORA_COL1  vec3(0.15,0.1,0.35)
#define NLC_AURORA_COL3 vec3(0.1,0.25,0.45)
#define NLC_AURORA_REFLECTION 5.0

/* Sky reflection */
//#define NL_GROUND_REFL 0.5       // [toggle] 0.2 slightly reflective ~ 1.0 fully reflect sky 
//#define NL_GROUND_AURORA_REFL    // [toggle] aurora reflection on ground
#define NL_RAIN_MIST_OPACITY 0.32 // [toggle] 0.04 very subtle ~ 0.5 thick mist blow
#define NL_GROUND_RAIN_WETNESS 0.8 // 0.0 no wetness ~ 1.0 fully wet blocks when raining
#define NL_GROUND_RAIN_PUDDLES 1.2 // 0.0 no puddles ~ 1.0 puddles

/* Chunk loading slide in animation */
//#define NL_CHUNK_LOAD_ANIM 100.0 // [toggle] -600.0 fall from top ~ 600.0 rise from bottom

/* Sun/Moon */
#define NL_SUNMOON_ANGLE 45.0 // [toggle] 0.0 no tilt - 90.0 tilt of 90 degrees
#define NL_SUNMOON_SIZE 1.1     // 0.3 tiny - 4.0 massive

#define NL_GODRAY 1.3

#define NLC_FAKE_DEPTH_TEX // [toggle] fake depth map when there are lighting around
#define NLC_END_REFLECTION 0.7

/* -------- CONFIG ENDS HERE ----------- */


/*
  EDITING CONFIG FOR SUBPACKS:
  
  If a value is already defined,
  then you must undefine it before modifying:
  eg: #undef OPTION_NAME

  subpack names and flags are inside pack_config.sh.
  pack.sh will enable corresponding flags when compiling. 
*/

/* ------ SUBPACK CONFIG STARTS HERE -------- */

#ifdef L_S_SC
  #define LOW_SATURATION
  #define SIMPLE_CLOUDS
#endif

#ifdef SIMPLE_CLOUDS
  #undef NL_CLOUD_TYPE
  #define NL_CLOUD_TYPE 1
#endif

#ifdef MULTILAYER
  #define NL_CLOUD2_MULTILAYER
  #undef NLC_CLOUD2_OPACITY
  #define NLC_CLOUD2_OPACITY 1.0
#endif

#ifdef GLOSSY_EFFECTS
  #define NL_GROUND_REFL 0.9
  #define NL_GROUND_AURORA_REFL
#endif

#ifdef NO_WPWAVE
 #undef NL_PLANTS_WAVE
 #undef NL_WATER_WAVE
#endif

#ifdef LOW_SATURATION
  #undef NL_TONEMAP_TYPE
  #undef NL_CONSTRAST
  #undef NL_EXPOSURE
  #undef NL_SATURATION
  #undef NL_SUN_INTENSITY

  #define NL_TONEMAP_TYPE 4
  #define NL_CONSTRAST 0.83
  #define NL_EXPOSURE 1.656
  #define NL_SATURATION 1.063
  #define NL_SUN_INTENSITY 2.85
#endif

/* ------ SUBPACK CONFIG ENDS HERE -------- */

#endif
