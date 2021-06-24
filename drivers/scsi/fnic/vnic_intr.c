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

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश "vnic_dev.h"
#समावेश "vnic_intr.h"

व्योम vnic_पूर्णांकr_मुक्त(काष्ठा vnic_पूर्णांकr *पूर्णांकr)
अणु
	पूर्णांकr->ctrl = शून्य;
पूर्ण

पूर्णांक vnic_पूर्णांकr_alloc(काष्ठा vnic_dev *vdev, काष्ठा vnic_पूर्णांकr *पूर्णांकr,
	अचिन्हित पूर्णांक index)
अणु
	पूर्णांकr->index = index;
	पूर्णांकr->vdev = vdev;

	पूर्णांकr->ctrl = vnic_dev_get_res(vdev, RES_TYPE_INTR_CTRL, index);
	अगर (!पूर्णांकr->ctrl) अणु
		prपूर्णांकk(KERN_ERR "Failed to hook INTR[%d].ctrl resource\n",
			index);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

व्योम vnic_पूर्णांकr_init(काष्ठा vnic_पूर्णांकr *पूर्णांकr, अचिन्हित पूर्णांक coalescing_समयr,
	अचिन्हित पूर्णांक coalescing_type, अचिन्हित पूर्णांक mask_on_निश्चितion)
अणु
	ioग_लिखो32(coalescing_समयr, &पूर्णांकr->ctrl->coalescing_समयr);
	ioग_लिखो32(coalescing_type, &पूर्णांकr->ctrl->coalescing_type);
	ioग_लिखो32(mask_on_निश्चितion, &पूर्णांकr->ctrl->mask_on_निश्चितion);
	ioग_लिखो32(0, &पूर्णांकr->ctrl->पूर्णांक_credits);
पूर्ण

व्योम vnic_पूर्णांकr_clean(काष्ठा vnic_पूर्णांकr *पूर्णांकr)
अणु
	ioग_लिखो32(0, &पूर्णांकr->ctrl->पूर्णांक_credits);
पूर्ण
