<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित LINUX_SSB_EMBEDDED_H_
#घोषणा LINUX_SSB_EMBEDDED_H_

#समावेश <linux/types.h>
#समावेश <linux/ssb/ssb.h>


बाह्य पूर्णांक ssb_watchकरोg_समयr_set(काष्ठा ssb_bus *bus, u32 ticks);

/* Generic GPIO API */
u32 ssb_gpio_in(काष्ठा ssb_bus *bus, u32 mask);
u32 ssb_gpio_out(काष्ठा ssb_bus *bus, u32 mask, u32 value);
u32 ssb_gpio_outen(काष्ठा ssb_bus *bus, u32 mask, u32 value);
u32 ssb_gpio_control(काष्ठा ssb_bus *bus, u32 mask, u32 value);
u32 ssb_gpio_पूर्णांकmask(काष्ठा ssb_bus *bus, u32 mask, u32 value);
u32 ssb_gpio_polarity(काष्ठा ssb_bus *bus, u32 mask, u32 value);

#पूर्ण_अगर /* LINUX_SSB_EMBEDDED_H_ */
