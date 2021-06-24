<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Linux driver क्रम digital TV devices equipped with B2C2 FlexcopII(b)/III
 * flexcop.h - निजी header file क्रम all flexcop-chip-source files
 * see flexcop.c क्रम copyright inक्रमmation
 */
#अगर_अघोषित __FLEXCOP_H__
#घोषणा __FLEXCOP_H__

#घोषणा FC_LOG_PREFIX "b2c2-flexcop"
#समावेश "flexcop-common.h"

बाह्य पूर्णांक b2c2_flexcop_debug;

/* debug */
#अगर_घोषित CONFIG_DVB_B2C2_FLEXCOP_DEBUG
#घोषणा dprपूर्णांकk(level, args...) \
	करो अणु अगर ((b2c2_flexcop_debug & (level))) prपूर्णांकk(args); पूर्ण जबतक (0)
#अन्यथा
#घोषणा dprपूर्णांकk(level, args...) no_prपूर्णांकk(args)
#पूर्ण_अगर

#घोषणा deb_info(args...) dprपूर्णांकk(0x01, args)
#घोषणा deb_tuner(args...) dprपूर्णांकk(0x02, args)
#घोषणा deb_i2c(args...) dprपूर्णांकk(0x04, args)
#घोषणा deb_ts(args...) dprपूर्णांकk(0x08, args)
#घोषणा deb_sram(args...) dprपूर्णांकk(0x10, args)
#घोषणा deb_rdump(args...) dprपूर्णांकk(0x20, args)
#घोषणा deb_i2c_dump(args...) dprपूर्णांकk(0x40, args)

#पूर्ण_अगर
