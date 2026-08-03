// main.mm
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <dlfcn.h>
#import <objc/runtime.h>
#include "Memory.h"
#include "ESP.h"
#include "SilentAim.h"
#include "Config.h"
#include "AntiCheat.h"
#include "Protection.h"

@interface GestureManager : NSObject
+ (instancetype)sharedInstance;
@end

@implementation GestureManager

+ (instancetype)sharedInstance {
    static GestureManager* instance = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        instance = [[GestureManager alloc] init];
        Class appClass = [UIApplication class];
        Method original = class_getInstanceMethod(appClass, @selector(sendEvent:));
        Method swizzled = class_getInstanceMethod(appClass, @selector(swizzled_sendEvent:));
        method_exchangeImplementations(original, swizzled);
    });
    return instance;
}

- (void)swizzled_sendEvent:(UIEvent *)event {
    if (event.type == UIEventTypeTouches) {
        NSSet* touches = [event allTouches];
        if (touches.count == 2) {
            BOOL allBegan = YES;
            for (UITouch* touch in touches) {
                if (touch.phase != UITouchPhaseBegan) { allBegan = NO; break; }
            }
            if (allBegan) {
                dispatch_async(dispatch_get_main_queue(), ^{
                    Config::toggle_esp();
                });
            }
        }
        if (touches.count == 3) {
            BOOL allBegan = YES;
            for (UITouch* touch in touches) {
                if (touch.phase != UITouchPhaseBegan) { allBegan = NO; break; }
            }
            if (allBegan) {
                dispatch_async(dispatch_get_main_queue(), ^{
                    Config::toggle_silent_aim();
                });
            }
        }
        if (touches.count == 4) {
            BOOL allBegan = YES;
            for (UITouch* touch in touches) {
                if (touch.phase != UITouchPhaseBegan) { allBegan = NO; break; }
            }
            if (allBegan) {
                dispatch_async(dispatch_get_main_queue(), ^{
                    Config::toggle_no_recoil();
                });
            }
        }
    }
    [self swizzled_sendEvent:event];
}

@end

Memory* g_memory = nullptr;

__attribute__((constructor))
void init_dylib() {
    Protection::init();
    [GestureManager sharedInstance];
    
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, 5 * NSEC_PER_SEC), dispatch_get_main_queue(), ^{
        g_memory = new Memory();
        AntiCheat::init(g_memory);
        AntiCheat::bypass();
        ESP::init(g_memory);
        SilentAim::init(g_memory);
    });
}

__attribute__((destructor))
void cleanup_dylib() {}