
#include "PathFinder.hpp"
#include <stdexcept>
#include <cstdlib>
#include <iostream>

PathFinder::PathFinder(const Image<Pixel> &img)
{
    load(img);
} // Constructor delegates to load() function

void PathFinder::load(const Image<Pixel> &img)
{
    // TODO
    //initializing start and end coords
    start={-1,-1};
    end={-1,-1};

    image=img; //stores image
    checkImage(img); //cecks image validity

    //getting the width and height
    int width=img.width();
    int height=img.height();

    //for loop to find the red pixel (start)
    for(int x=0;x<width;++x){
        for(int y=0;y<height;++y){
            if(img(x,y)==RED){
                start={x,y}; //starting coords
            }
        }
    }
    //error if no red is present
    if(start.row==-1||start.col==-1){
        throw std::runtime_error("start pt not found");
    }
}

PathFinder::~PathFinder()
{
    clear();
} // Destructor delegates to clear() function

void PathFinder::checkImage(const Image<Pixel> &img)
{
    // TODO
    //getting image width and height
    int height = img.height();
    int width = img.width();

    //# of red (start) spots
    int redspots = 0;

    //looping through pixels
    for (int x=0;x<width;x++) {
        for(int y=0;y<height;y++) {
            Pixel px=img(x,y);
            if(px==RED) {
                //if red increment how many red pizels there are
                ++redspots;
                //invalid color found if not one of these
            } else if (px!= WHITE && px!= BLACK && px!=RED) {
                throw std::invalid_argument("invalid colors in pic");
            }
        }
    }
    if (redspots != 1) {
        throw std::invalid_argument("can only be one red spot in pic (start pt)");
    
    }
}  


void PathFinder::findPath(std::string strategy)
{
    // TODO, strategy is default at "NSWE"
    // Must use Queue ADT to implement BFS algorithm


    //BFS queue
    Queue<Coord, List<Coord>> queue;
    //tracking which coordinates we have passed through
    std::vector<std::vector<int>> visited(image.height(), std::vector<int>(image.width(), 0));
    //getting the height and width again
    int height =image.height();
    int width =image.width();
    //parent mapping
    std::vector<std::vector<Coord>> parents(height,std::vector<Coord>(width,{-1,-1}));

    queue.enqueue(start);
    visited[start.row][start.col] = 1;
    Coord pos = start;

    while (!queue.isEmpty()) {
        //getting the next coord
        pos = queue.peekFront();
        //removing it from the queue
        queue.dequeue();

        //checking if you can exit 
        if (pos.row == 0 || pos.col == 0 || pos.row == image.width() - 1 || pos.col == image.height() - 1) {
            //setting the end coord as current coord
            end = pos;
            Coord current =end;
            //used to mark the path (yellow)
            while(current != start){
                Coord previous = parents[current.row][current.col];
                if(previous!=start){
                    image(previous.row,previous.col)=YELLOW;
                }
                current=previous;
            }
            //marking the end point
            image(end.row,end.col)=GREEN;
            return;
        }

        //using the strategy to move
        for (int i = 0; i < strategy.length(); i++) {
            char dir = strategy[i];  // Get the current dir
            Coord next = pos;         // Starting from the current pos
        
            //directions of NSEW
            //moving based on direction
            if (dir == 'N') {
                next.row--; 
            } else if (dir == 'S') {
                next.row++;  
            } else if (dir == 'W') {
                next.col--;  
            } else if (dir == 'E') {
                next.col++;  
            }

            //added bounds check to see if next is inside the img
            if(next.row<0||next.row>=image.height()||next.col<0||next.col>=image.width()){
                continue;//skips if its out of bounds
                //if in this loop still next pos is valid
            }
            //if white and not visitied
            if (image(next.row, next.col) == WHITE && visited[next.row][next.col] == 0) {
                visited[next.row][next.col] = 1;
                parents[next.row][next.col]=pos;
                queue.enqueue(next);//adding to the queue
            }
        }
    }
    //error if not path was found
    throw std::runtime_error("no path");
}




void PathFinder::findPathWithVisualization(const std::string &outfile, int frame_duration, int frame_gap, std::string strategy)
{
    // frame_duration and frame_gap should stay the same throughout the function

    // Initialize GIF writer
    int cell_size = 1; // Each cell is 1x1 pixels, you can change this to a larger size if needed
    int gif_height = image.height() * cell_size;
    int gif_width = image.width() * cell_size;

    int frame_counter = 0; // each movement is a frame and you can define how frequently you want to write the frame

    GifWriter gif; // a gif object has been declared and is pending for writing
    if (!GifBegin(&gif, (outfile + ".gif").c_str(), gif_width, gif_height, frame_duration, 8, true))
    {
        throw std::runtime_error("Failed to create GIF file.");
    }

    // TODO, strategy is default at "NSWE"
    // Must use Queue ADT to implement BFS algorithm with visualization

    // Must use `` addFrameToGif(gif, frame_duration) `` at certain time to write the frame to the gif
    // Before each of your function exit (e.g., return or throw), you have to conclude the gif object
    // by `` GifEnd(&gif); ``

    // It's also expected to have
    // ``writeToFile(image, outfile + "_final_visual.png")`` at the end of pathfinding

    

    GifEnd(&gif);
}

// Helper function
void PathFinder::addFrameToGif(GifWriter &gif, int frame_duration)
{
    // Each coordinate is 1x1 pixels, you can change this to a larger size if needed
    int cell_size = 1;
    int gif_height = image.height() * cell_size;
    int gif_width = image.width() * cell_size;
    // 4 is the number of channels (RGBA)
    std::vector<uint8_t> rgb_data(gif_height * gif_width * 4);

    // Convert the image to RGB format for the GIF
    for (int r = 0; r < image.height(); ++r)
    {
        for (int c = 0; c < image.width(); ++c)
        {
            Pixel color;
            if (image(r, c) == WHITE)
            {
                color = {255, 255, 255};
            }
            else if (image(r, c) == BLACK)
            {
                color = {0, 0, 0};
            }
            else if (image(r, c) == RED)
            {
                color = {255, 0, 0};
            }
            else if (image(r, c) == GREEN)
            {
                color = {0, 255, 0};
            }
            else if (image(r, c) == BLUE)
            {
                color = {0, 0, 255};
            }
            else if (image(r, c) == YELLOW)
            {
                color = {255, 255, 0};
            }
            else
            {
                color = {0, 0, 0};
            }

            // Fill the cell with the color
            for (int i = 0; i < cell_size; ++i)
            {
                for (int j = 0; j < cell_size; ++j)
                {
                    int pixel_row = r * cell_size + i;
                    int pixel_col = c * cell_size + j;
                    int index = (pixel_row * gif_width + pixel_col) * 4;
                    rgb_data[index + 0] = color.red;
                    rgb_data[index + 1] = color.green;
                    rgb_data[index + 2] = color.blue;
                    rgb_data[index + 3] = 255; // Alpha channel
                }
            }
        }
    }
    // Write the frame to the GIF
    GifWriteFrame(&gif, rgb_data.data(), gif_width, gif_height, frame_duration, 8, true);
} // Finished

void PathFinder::writeSolutionToFile(const std::string &filename)
{
    writeToFile(image, filename);
} // delegate to writeToFile function in lib/image.h

Coord PathFinder::getStart()
{
    // TODO
    //returns the starting coord
    return start; // placeholder
}

Coord PathFinder::getEnd()
{
    // TODO
    //retruns the ending coord
    return end; // placeholder
}

void PathFinder::clear()
{
    // TODO
    //reseting the internal original state
   start={-1,-1};
   end={-1,-1};
   next={-1,-1};
}








// Nonmember functions
bool compareImagesExit(std::string img1_str, std::string img2_str)
{
    Image<Pixel> img1 = readFromFile(img1_str);
    Image<Pixel> img2 = readFromFile(img2_str);
    if (img1.width() != img2.width() || img1.height() != img2.height())
    {
        return false;
    }
    for (int r = 0; r < img1.height(); ++r)
    {
        for (int c = 0; c < img1.width(); ++c)
        {
            // Check if the pixels are different and one of them is GREEN
            if (img1(r, c) != img2(r, c) && (img1(r, c) == GREEN || img2(r, c) == GREEN))
            {
                return false;
            }
        }
    }
    return true;
} // Finished

bool compareImages(std::string img1_str, std::string img2_str)
{
    Image<Pixel> img1 = readFromFile(img1_str);
    Image<Pixel> img2 = readFromFile(img2_str);
    if (img1.width() != img2.width() || img1.height() != img2.height())
    {
        return false;
    }
    for (int r = 0; r < img1.height(); ++r)
    {
        for (int c = 0; c < img1.width(); ++c)
        {
            if (img1(r, c) != img2(r, c))
            {
                return false;
            }
        }
    }
    return true;
} // Finished
