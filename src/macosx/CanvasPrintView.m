
/**
 * OpenEmulator
 * Mac OS X Canvas Print View
 * (C) 2011 by Marc S. Ressl (mressl@umich.edu)
 * Released under the GPL
 *
 * Controls a canvas print view
 */

#import "CanvasPrintView.h"

@implementation CanvasPrintView

- (id)initWithCanvasView:(CanvasView *)theCanvasView
{
    NSSize pixelDensity = [theCanvasView canvasPixelDensity];
    NSSize scale = NSMakeSize(72.0F / pixelDensity.width,
                              72.0F / pixelDensity.height);
    
    NSSize frameSize = [theCanvasView canvasSize];
    NSRect frame = NSMakeRect(0, 0,
                              frameSize.width * scale.width,
                              frameSize.height * scale.height);
    
    self = [super initWithFrame:frame];
    
    if (self)
        canvasView = theCanvasView;
    
    return self;
}

- (BOOL)isOpaque
{
    return YES;
}

- (BOOL)isFlipped
{
    return [canvasView isPaperCanvas];
}

- (void)drawRect:(NSRect)theRect
{
    NSSize pixelDensity = [canvasView canvasPixelDensity];
    NSSize scale = NSMakeSize(pixelDensity.width / 72,
                              pixelDensity.height / 72);
    
    NSRect ourRect = NSMakeRect(theRect.origin.x * scale.width,
                                theRect.origin.y * scale.height,
                                theRect.size.width * scale.width,
                                theRect.size.height * scale.height);
    
    NSImage *image = [canvasView canvasImage:ourRect];
    
    [image drawInRect:theRect
             fromRect:NSZeroRect
            operation:NSCompositeSourceOver
             fraction:1];
}

@end
