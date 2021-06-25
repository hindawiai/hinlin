<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  Copyright (C) 2012 John Crispin <john@phrozen.org>
 */

#अगर_अघोषित _RT288X_PINMUX_H__
#घोषणा _RT288X_PINMUX_H__

#घोषणा FUNC(name, value, pin_first, pin_count) \
	अणु name, value, pin_first, pin_count पूर्ण

#घोषणा GRP(_name, _func, _mask, _shअगरt) \
	अणु .name = _name, .mask = _mask, .shअगरt = _shअगरt, \
	  .func = _func, .gpio = _mask, \
	  .func_count = ARRAY_SIZE(_func) पूर्ण

#घोषणा GRP_G(_name, _func, _mask, _gpio, _shअगरt) \
	अणु .name = _name, .mask = _mask, .shअगरt = _shअगरt, \
	  .func = _func, .gpio = _gpio, \
	  .func_count = ARRAY_SIZE(_func) पूर्ण

काष्ठा rt2880_pmx_group;

काष्ठा rt2880_pmx_func अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर value;

	पूर्णांक pin_first;
	पूर्णांक pin_count;
	पूर्णांक *pins;

	पूर्णांक *groups;
	पूर्णांक group_count;

	पूर्णांक enabled;
पूर्ण;

काष्ठा rt2880_pmx_group अणु
	स्थिर अक्षर *name;
	पूर्णांक enabled;

	स्थिर u32 shअगरt;
	स्थिर अक्षर mask;
	स्थिर अक्षर gpio;

	काष्ठा rt2880_pmx_func *func;
	पूर्णांक func_count;
पूर्ण;

बाह्य काष्ठा rt2880_pmx_group *rt2880_pinmux_data;

#पूर्ण_अगर
