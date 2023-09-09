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
 * it requires the 'RENDER_TO_FRAME