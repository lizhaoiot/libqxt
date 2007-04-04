/****************************************************************************
**
** Copyright (C) Qxt Foundation. Some rights reserved.
**
** This file is part of the QxtCore module of the Qt eXTension library
**
** This library is free software; you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License as published by the Free Software Foundation; either
** version 2.1 of the License, or any later version.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
** There is aditional information in the LICENSE file of libqxt.
** If you did not receive a copy of the file try to download it or
** contact the libqxt Management
** 
** <http://libqxt.sourceforge.net>  <aep@exys.org>  <coda@bobandgeorge.com>
**
****************************************************************************/


#include "QxtApplication.h"
#include <qt_windows.h>
#include <QWidget>

bool QxtApplication::winEventFilter(MSG* msg, long* result)
{
	if (msg->message == WM_HOTKEY)
	{
		uint modifiers = LOWORD(msg->lParam);
		uint keycode = HIWORD(msg->lParam);
		activateHotKey(modifiers, keycode);
	}
	return QApplication::winEventFilter(msg, result);
}

uint QxtApplication::nativeModifiers(Qt::KeyboardModifiers modifiers) const
{
	// MOD_ALT, MOD_CONTROL, (MOD_KEYUP), MOD_SHIFT, MOD_WIN
	uint native = 0;
	if (modifiers & Qt::ShiftModifier)
		native |= MOD_SHIFT;
	if (modifiers & Qt::ControlModifier)
		native |= MOD_CONTROL;
	if (modifiers & Qt::AltModifier)
		native |= MOD_ALT;
	if (modifiers & Qt::MetaModifier)
		native |= MOD_WIN;
	// TODO: resolve these?
	//if (modifiers & Qt::KeypadModifier)
	//if (modifiers & Qt::GroupSwitchModifier)
	return native;
}

uint QxtApplication::nativeKeycode(Qt::Key key) const
{
	switch (key)
	{
	case Qt::Key_Escape:		return VK_ESCAPE;
	case Qt::Key_Tab:			
	case Qt::Key_Backtab:		return VK_TAB;
	case Qt::Key_Backspace:		return VK_BACK;
	case Qt::Key_Return:
	case Qt::Key_Enter:			return VK_RETURN;
	case Qt::Key_Insert:		return VK_INSERT;
	case Qt::Key_Delete:		return VK_DELETE;
	case Qt::Key_Pause:			return VK_PAUSE;
	case Qt::Key_Print:			return VK_PRINT;
	case Qt::Key_Clear:			return VK_CLEAR;
	case Qt::Key_Home:			return VK_HOME;
	case Qt::Key_End:			return VK_END;
	case Qt::Key_Left:			return VK_LEFT;
	case Qt::Key_Up:			return VK_UP;
	case Qt::Key_Right:			return VK_RIGHT;
	case Qt::Key_Down:			return VK_DOWN;
	case Qt::Key_PageUp:		return VK_PRIOR;
	case Qt::Key_PageDown:		return VK_NEXT;
	case Qt::Key_F1:			return VK_F1;
	case Qt::Key_F2:			return VK_F2;
	case Qt::Key_F3:			return VK_F3;
	case Qt::Key_F4:			return VK_F4;
	case Qt::Key_F5:			return VK_F5;
	case Qt::Key_F6:			return VK_F6;
	case Qt::Key_F7:			return VK_F7;
	case Qt::Key_F8:			return VK_F8;
	case Qt::Key_F9:			return VK_F9;
	case Qt::Key_F10:			return VK_F10;
	case Qt::Key_F11:			return VK_F11;
	case Qt::Key_F12:			return VK_F12;
	case Qt::Key_F13:			return VK_F13;
	case Qt::Key_F14:			return VK_F14;
	case Qt::Key_F15:			return VK_F15;
	case Qt::Key_F16:			return VK_F16;
	case Qt::Key_F17:			return VK_F17;
	case Qt::Key_F18:			return VK_F18;
	case Qt::Key_F19:			return VK_F19;
	case Qt::Key_F20:			return VK_F20;
	case Qt::Key_F21:			return VK_F21;
	case Qt::Key_F22:			return VK_F22;
	case Qt::Key_F23:			return VK_F23;
	case Qt::Key_F24:			return VK_F24;
	case Qt::Key_Space:			return VK_SPACE;
	case Qt::Key_Asterisk:		return VK_MULTIPLY;
	case Qt::Key_Plus:			return VK_ADD;
	case Qt::Key_Comma:			return VK_SEPARATOR;
	case Qt::Key_Minus:			return VK_SUBTRACT;
	case Qt::Key_Slash:			return VK_DIVIDE;

		// numbers
	case Qt::Key_0:
	case Qt::Key_1:
	case Qt::Key_2:
	case Qt::Key_3:
	case Qt::Key_4:
	case Qt::Key_5:
	case Qt::Key_6:
	case Qt::Key_7:
	case Qt::Key_8:
	case Qt::Key_9:				return key;

		// letters
	case Qt::Key_A:
	case Qt::Key_B:
	case Qt::Key_C:
	case Qt::Key_D:
	case Qt::Key_E:
	case Qt::Key_F:
	case Qt::Key_G:
	case Qt::Key_H:
	case Qt::Key_I:
	case Qt::Key_J:
	case Qt::Key_K:
	case Qt::Key_L:
	case Qt::Key_M:
	case Qt::Key_N:
	case Qt::Key_O:
	case Qt::Key_P:
	case Qt::Key_Q:
	case Qt::Key_R:
	case Qt::Key_S:
	case Qt::Key_T:
	case Qt::Key_U:
	case Qt::Key_V:
	case Qt::Key_W:
	case Qt::Key_X:
	case Qt::Key_Y:
	case Qt::Key_Z:				return key;

	default:					return 0;
	}
}

bool QxtApplication::registerHotKey(uint modifiers, uint keycode, QWidget* receiver)
{
	Q_ASSERT(receiver);
	return RegisterHotKey(receiver->winId(), modifiers ^ keycode, modifiers, keycode);
}

bool QxtApplication::unregisterHotKey(uint modifiers, uint keycode, QWidget* receiver)
{
	Q_ASSERT(receiver);
	return UnregisterHotKey(receiver->winId(), modifiers ^ keycode);
}
