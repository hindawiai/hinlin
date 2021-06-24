<शैली गुरु>
/*
 * B53 platक्रमm data
 *
 * Copyright (C) 2013 Jonas Gorski <jogo@खोलोwrt.org>
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#अगर_अघोषित __B53_H
#घोषणा __B53_H

#समावेश <linux/types.h>
#समावेश <linux/platक्रमm_data/dsa.h>

काष्ठा b53_platक्रमm_data अणु
	/* Must be first such that dsa_रेजिस्टर_चयन() can access it */
	काष्ठा dsa_chip_data cd;

	u32 chip_id;
	u16 enabled_ports;

	/* only used by MMAP'd driver */
	अचिन्हित big_endian:1;
	व्योम __iomem *regs;
पूर्ण;

#पूर्ण_अगर
