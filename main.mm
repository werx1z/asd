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

// ============================================================
//  👆 GESTURE MANAGER (для управления жестами)
// ============================================================
@interface GestureManager : NSObject
+ (instancetype)sharedInstance;
@end

@implementation GestureManager

+ (instancetype)sharedInstance {
    static GestureManager* instance = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        instance = [[GestureManager alloc] init];
        
        // Перехватываем касания через UIApplication
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
        
        // 2 пальца → ESP
        if (touches.count == 2) {
            BOOL allBegan = YES;
            for (UITouch* touch in touches) {
                if (touch.phase != UITouchPhaseBegan) {
                    allBegan = NO;
                    break;
                }
            }
            if (allBegan) {
                dispatch_async(dispatch_get_main_queue(), ^{
                    Config::toggle_esp();
                });
            }
        }
        
        // 3 пальца → Silent Aim
        if (touches.count == 3) {
            BOOL allBegan = YES;
            for (UITouch* touch in touches) {
                if (touch.phase != UITouchPhaseBegan) {
                    allBegan = NO;
                    break;
                }
            }
            if (allBegan) {
                dispatch_async(dispatch_get_main_queue(), ^{
                    Config::toggle_silent_aim();
                });
            }
        }
        
        // 4 пальца → No Recoil
        if (touches.count == 4) {
            BOOL allBegan = YES;
            for (UITouch* touch in touches) {
                if (touch.phase != UITouchPhaseBegan) {
                    allBegan = NO;
                    break;
                }
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

// ============================================================
//  🚀 ГЛАВНАЯ ФУНКЦИЯ
// ============================================================
Memory* g_memory = nullptr;

__attribute__((constructor))
void init_dylib() {
    // Активируем жесты
    [GestureManager sharedInstance];
    
    // Ждём 5 секунд, пока игра полностью загрузится
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, 5 * NSEC_PER_SEC), dispatch_get_main_queue(), ^{
        // Создаём объект для чтения памяти
        g_memory = new Memory();
        
        // Байпасс античита
        AntiCheat::init(g_memory);
        AntiCheat::bypass();
        
        // Инициализируем ESP и Silent Aim
        ESP::init(g_memory);
        SilentAim::init(g_memory);
    });
}

__attribute__((destructor))
void cleanup_dylib() {
    // Очистка при выгрузке
}
