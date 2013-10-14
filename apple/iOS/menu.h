/*  RetroArch - A frontend for libretro.
 *  Copyright (C) 2013 - Jason Fetters
 * 
 *  RetroArch is free software: you can redistribute it and/or modify it under the terms
 *  of the GNU General Public License as published by the Free Software Found-
 *  ation, either version 3 of the License, or (at your option) any later version.
 *
 *  RetroArch is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 *  without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 *  PURPOSE.  See the GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along with RetroArch.
 *  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __APPLE_RARCH_IOS_MENU_H__
#define __APPLE_RARCH_IOS_MENU_H__

#include "frontend/menu/history.h"
#include "views.h"
#include "apple/common/setting_data.h"

@protocol RAMenuItemBase
- (UITableViewCell*)cellForTableView:(UITableView*)tableView;
- (void)wasSelectedOnTableView:(UITableView*)tableView ofController:(UIViewController*)controller;
@end

/*********************************************/
/* RAMenuBase                                */
/* A menu class that displays RAMenuItemBase */
/* objects.                                  */
/*********************************************/
@interface RAMenuBase : RATableViewController @end

/*********************************************/
/* RAMenuItemBasic                           */
/* A simple menu item that displays a text   */
/* description and calls a block object when */
/* selected.                                 */
/*********************************************/
@interface RAMenuItemBasic : NSObject<RAMenuItemBase>
@property (nonatomic) NSString* description;
@property (nonatomic) id userdata;
@property (copy) void (^action)(id userdata);
@property (copy) NSString* (^detail)(id userdata);
@end

/*********************************************/
/* RAMenuItemBoolean                         */
/* A simple menu item that displays the      */
/* state, and allows editing, of a boolean   */
/* setting.                                  */
/*********************************************/
@interface RAMenuItemBoolean : NSObject<RAMenuItemBase>
@property (nonatomic) const rarch_setting_t* setting;
@end

/*********************************************/
/* RAMenuItemString                          */
/* A simple menu item that displays the      */
/* state, and allows editing, of a string or */
/* numeric setting.                          */
/*********************************************/
@interface RAMenuItemString : NSObject<RAMenuItemBase, UIAlertViewDelegate>
@property (nonatomic) const rarch_setting_t* setting;
@property (nonatomic, weak) UITableView* parentTable;
@end

/*********************************************/
/* RAMenuItemPathSetting                     */
/* A menu item that displays and allows      */
/* browsing for a path setting.              */
/*********************************************/
@interface RAMenuItemPathSetting : RAMenuItemString<RAMenuItemBase, RADirectoryListDelegate> @end

/*********************************************/
/* RAMenuItemBindSetting                     */
/* A menu item that displays and allows      */
/* mapping of a keybinding.                  */
/*********************************************/
@interface RAMenuItemBindSetting : RAMenuItemString<RAMenuItemBase, UIAlertViewDelegate> @end

/*********************************************/
/* RAMainMenu                                */
/* Menu object that is displayed immediately */
/* after startup.                            */
/*********************************************/
@interface RAMainMenu : RAMenuBase<RADirectoryListDelegate>
@property (nonatomic) NSString* core;
@end

/*********************************************/
/* RAHistoryMenu                             */
/* Menu object that displays and allows      */
/* launching a file from the ROM history.    */
/*********************************************/
@interface RAHistoryMenu : RAMenuBase
@property (nonatomic) rom_history_t* history;
- (id)initWithHistoryPath:(NSString*)historyPath;
@end

/*********************************************/
/* RAFrontendSettingsMenu                    */
/* Menu object that displays and allows      */
/* editing of cocoa frontend related         */
/* settings.                                 */
/*********************************************/
@interface RAFrontendSettingsMenu : RAMenuBase<UIAlertViewDelegate> @end

/*********************************************/
/* RACoreSettingsMenu                        */
/* Menu object that displays and allows      */
/* editing of the setting_data list.         */
/*********************************************/
@interface RACoreSettingsMenu : RAMenuBase
@property (nonatomic) NSString* core;
- (id)initWithCore:(NSString*)core;
@end

/*********************************************/
/* RAMenuItemCoreList                        */
/* Menu item that handles display and        */
/* selection of an item in RAMenuCoreList.   */
/* This item will not function on anything   */
/* but an RAMenuCoreList type menu.          */
/*********************************************/
@class RAMenuCoreList;
@interface RAMenuItemCoreList : NSObject<RAMenuItemBase>
@property (nonatomic, weak) RAMenuCoreList* parent;
@property (nonatomic) NSString* core;
@end

/*********************************************/
/* RAMenuCoreList                            */
/* Menu object that displays and allows      */
/* selection from a list of cores.           */
/* If the path is not nil, only cores that   */
/* may support the file is listed.           */
/* If the path is nil, an 'Auto Detect'      */
/* entry is added to the menu, when tapped   */
/* the action function will be called with   */
/* nil as the argument.                      */
/*********************************************/
@interface RAMenuCoreList : RAMenuBase
@property (nonatomic) NSString* path;
@property (copy) void (^action)(NSString* coreID);
- (id)initWithPath:(NSString*)path action:(void (^)(NSString*))action;
@end

#endif
