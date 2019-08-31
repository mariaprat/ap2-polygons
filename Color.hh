#ifndef Color_hh
#define Color_hh

/** The Color class stores an RGB Color with components in [0,1].
    Usually, (0,0,0) gives black color and (1,1,1) gives white color. */

// *****************************************************************************

class Color  {
    private:
        /* Red (r), green (g) and blue (b) components. */
        double r, g, b;

    public:
        /* Constructor. By default, Color() gives black color. */
        Color (double r = 0, double g = 0, double b = 0);

        /* Gets the red (r) component. */
        double get_R () const;

        /* Gets the green (g) component. */
        double get_G () const;

        /* Gets the blue (b) componemt. */
        double get_B () const;
};


#endif
