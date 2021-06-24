<शैली गुरु>
/*
 * Copyright 2008 Cisco Systems, Inc.  All rights reserved.
 * Copyright 2007 Nuova Systems, Inc.  All rights reserved.
 *
 * This program is मुक्त software; you may redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#अगर_अघोषित _VNIC_INTR_H_
#घोषणा _VNIC_INTR_H_

#समावेश <linux/pci.h>
#समावेश "vnic_dev.h"

/*
 * These defines aव्योम symbol clash between fnic and enic (Cisco 10G Eth
 * Driver) when both are built with CONFIG options =y
 */
#घोषणा vnic_पूर्णांकr_unmask fnic_पूर्णांकr_unmask
#घोषणा vnic_पूर्णांकr_mask fnic_पूर्णांकr_mask
#घोषणा vnic_पूर्णांकr_वापस_credits fnic_पूर्णांकr_वापस_credits
#घोषणा vnic_पूर्णांकr_credits fnic_पूर्णांकr_credits
#घोषणा vnic_पूर्णांकr_वापस_all_credits fnic_पूर्णांकr_वापस_all_credits
#घोषणा vnic_पूर्णांकr_legacy_pba fnic_पूर्णांकr_legacy_pba
#घोषणा vnic_पूर्णांकr_मुक्त fnic_पूर्णांकr_मुक्त
#घोषणा vnic_पूर्णांकr_alloc fnic_पूर्णांकr_alloc
#घोषणा vnic_पूर्णांकr_init fnic_पूर्णांकr_init
#घोषणा vnic_पूर्णांकr_clean fnic_पूर्णांकr_clean

#घोषणा VNIC_INTR_TIMER_MAX		0xffff

#घोषणा VNIC_INTR_TIMER_TYPE_ABS	0
#घोषणा VNIC_INTR_TIMER_TYPE_QUIET	1

/* Interrupt control */
काष्ठा vnic_पूर्णांकr_ctrl अणु
	u32 coalescing_समयr;		/* 0x00 */
	u32 pad0;
	u32 coalescing_value;		/* 0x08 */
	u32 pad1;
	u32 coalescing_type;		/* 0x10 */
	u32 pad2;
	u32 mask_on_निश्चितion;		/* 0x18 */
	u32 pad3;
	u32 mask;			/* 0x20 */
	u32 pad4;
	u32 पूर्णांक_credits;		/* 0x28 */
	u32 pad5;
	u32 पूर्णांक_credit_वापस;		/* 0x30 */
	u32 pad6;
पूर्ण;

काष्ठा vnic_पूर्णांकr अणु
	अचिन्हित पूर्णांक index;
	काष्ठा vnic_dev *vdev;
	काष्ठा vnic_पूर्णांकr_ctrl __iomem *ctrl;	/* memory-mapped */
पूर्ण;

अटल अंतरभूत व्योम vnic_पूर्णांकr_unmask(काष्ठा vnic_पूर्णांकr *पूर्णांकr)
अणु
	ioग_लिखो32(0, &पूर्णांकr->ctrl->mask);
पूर्ण

अटल अंतरभूत व्योम vnic_पूर्णांकr_mask(काष्ठा vnic_पूर्णांकr *पूर्णांकr)
अणु
	ioग_लिखो32(1, &पूर्णांकr->ctrl->mask);
पूर्ण

अटल अंतरभूत व्योम vnic_पूर्णांकr_वापस_credits(काष्ठा vnic_पूर्णांकr *पूर्णांकr,
	अचिन्हित पूर्णांक credits, पूर्णांक unmask, पूर्णांक reset_समयr)
अणु
#घोषणा VNIC_INTR_UNMASK_SHIFT		16
#घोषणा VNIC_INTR_RESET_TIMER_SHIFT	17

	u32 पूर्णांक_credit_वापस = (credits & 0xffff) |
		(unmask ? (1 << VNIC_INTR_UNMASK_SHIFT) : 0) |
		(reset_समयr ? (1 << VNIC_INTR_RESET_TIMER_SHIFT) : 0);

	ioग_लिखो32(पूर्णांक_credit_वापस, &पूर्णांकr->ctrl->पूर्णांक_credit_वापस);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक vnic_पूर्णांकr_credits(काष्ठा vnic_पूर्णांकr *पूर्णांकr)
अणु
	वापस ioपढ़ो32(&पूर्णांकr->ctrl->पूर्णांक_credits);
पूर्ण

अटल अंतरभूत व्योम vnic_पूर्णांकr_वापस_all_credits(काष्ठा vnic_पूर्णांकr *पूर्णांकr)
अणु
	अचिन्हित पूर्णांक credits = vnic_पूर्णांकr_credits(पूर्णांकr);
	पूर्णांक unmask = 1;
	पूर्णांक reset_समयr = 1;

	vnic_पूर्णांकr_वापस_credits(पूर्णांकr, credits, unmask, reset_समयr);
पूर्ण

अटल अंतरभूत u32 vnic_पूर्णांकr_legacy_pba(u32 __iomem *legacy_pba)
अणु
	/* पढ़ो PBA without clearing */
	वापस ioपढ़ो32(legacy_pba);
पूर्ण

व्योम vnic_पूर्णांकr_मुक्त(काष्ठा vnic_पूर्णांकr *पूर्णांकr);
पूर्णांक vnic_पूर्णांकr_alloc(काष्ठा vnic_dev *vdev, काष्ठा vnic_पूर्णांकr *पूर्णांकr,
	अचिन्हित पूर्णांक index);
व्योम vnic_पूर्णांकr_init(काष्ठा vnic_पूर्णांकr *पूर्णांकr, अचिन्हित पूर्णांक coalescing_समयr,
	अचिन्हित पूर्णांक coalescing_type, अचिन्हित पूर्णांक mask_on_निश्चितion);
व्योम vnic_पूर्णांकr_clean(काष्ठा vnic_पूर्णांकr *पूर्णांकr);

#पूर्ण_अगर /* _VNIC_INTR_H_ */
