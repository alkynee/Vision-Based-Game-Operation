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
const int SAMPLE_AREA_HEI