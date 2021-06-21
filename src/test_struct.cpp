#include "test_struct.h"

typedef struct Video {
    const char *name;
    int unique_views;
} Video;

typedef struct Viewer {
    const char *username;
    Video *watched_videos;
    int watched_videos_size;
} Viewer;

int count_views(Viewer **viewers, int viewers_size, const char *video_name)
{
    int ret = 0;
    // Waiting to be implemented
    for(int i = 0; i < viewers_size; i++)
    {
        for(int j = 0; j < viewers[i]->watched_videos_size; j++)
        {
            if(!strcmp(viewers[i]->watched_videos[j].name, video_name))
            {
                ret++;
            }
        }
    }
    return ret;
}

/* It should return the number of viewers who have watched a video with the name video_name
 * calling count_views(viewers, 1, "Soccer") should return 1.
 */
int test_struct()
{
    Video videos[] = { {.name = "Soccer", .unique_views = 500},
                       {.name = "Basketball", .unique_views = 1000} };
    Viewer viewer = {.username = "Dave", .watched_videos = videos,
                     .watched_videos_size = 2};

    Viewer *viewers[] = { &viewer };
    printf("%d\n", count_views(viewers, 1, "Soccer")); // should print 1
    return 0;
}
