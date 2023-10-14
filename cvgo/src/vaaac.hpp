/*
 * MIT License
 * Copyright (c) 2020 Pablo Peñarroja
 */

/*
 * the following constants should be
 * altered in order to fit the user's
 * needs.
 * they're set to standard values
 * by default, and changing them may
 * dramatically alter the library's
 * behaviour
 */

 //                                   //
 //-------- c o n s t a n t s --------//
 //                                   //

/*
 * this indicates whether to render
 * the processed image to a matrix
 * 'frame'.
 * this matrix can be retrieved using
 * the 'getFrame()' method declared
 * bellow
 */
const bool RENDER_TO_FRAME = true;

/*
 * this indicates whether to create a
 * separate window and render the
 * current frame to that window.
 * it requires the 'RENDER_TO_FRAME'
 * constant to be true
 */
const bool RENDER_TO_WINDOW = true;

/*
 * this indicates whether to render
 * a small text explaining to the user
 * what to do
 */
const bool RENDER_SAMPLE_TEXT = true;

/*
 * width and height of the skin color
 * sampling rectangle
 */
const int SAMPLE_AREA_WIDTH = 30;
const int SAMPLE_AREA_HEIGHT = 30;

/*
 * this is the tolerance applied to
 * the lower and higher bounds of the
 * HSV skin tone color sampled from
 * the user.
 * low values limit the range, thus
 *
 */
const int MASK_LOW_TOLERANCE = 50;
const int MASK_HIGH_TOLERANCE = 25;

/*
 * width and height of the reticle:
 * the area centered at the middle of
 * the screen where the program will
 * look for the user's skin.
 * in case of finding it, the object
 * union find algorithm will start.
 */
const int RETICLE_SIZE = 40;

/*
 * if an object is detected, but the
 * aim point is located within this
 * area, the aim point will be instantly
 * set to zero.
 * the reason for this being that it's
 * very hard to distinguish the accurate
 * location of the aim point when the
 * user is pointing straight at the
 * camera
 */
const int NO_AIM_AREA_SIZE = 80;

/*
 * the bfs sample size represents the
 * square root of the area to scan for
 * each node of the bfs algorithm.
 * the lower this value, the more
 * accurate but the more noise, and the
 * more cpu usage required as well
 */
const int BFS_SAMPLE_SIZE = 2;

/*
 * smoothness is used to get rid of some
 * of the noise in the calculations.
 * the higher this number, the more
 * smoothnes