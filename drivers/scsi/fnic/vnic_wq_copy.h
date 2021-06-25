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
#अगर_अघोषित _VNIC_WQ_COPY_H_
#घोषणा _VNIC_WQ_COPY_H_

#समावेश <linux/pci.h>
#समावेश "vnic_wq.h"
#समावेश "fcpio.h"

#घोषणा	VNIC_WQ_COPY_MAX 1

काष्ठा vnic_wq_copy अणु
	अचिन्हित पूर्णांक index;
	काष्ठा vnic_dev *vdev;
	काष्ठा vnic_wq_ctrl __iomem *ctrl;	/* memory-mapped */
	काष्ठा vnic_dev_ring ring;
	अचिन्हित to_use_index;
	अचिन्हित to_clean_index;
पूर्ण;

अटल अंतरभूत अचिन्हित पूर्णांक vnic_wq_copy_desc_avail(काष्ठा vnic_wq_copy *wq)
अणु
	वापस wq->ring.desc_avail;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक vnic_wq_copy_desc_in_use(काष्ठा vnic_wq_copy *wq)
अणु
	वापस wq->ring.desc_count - 1 - wq->ring.desc_avail;
पूर्ण

अटल अंतरभूत व्योम *vnic_wq_copy_next_desc(काष्ठा vnic_wq_copy *wq)
अणु
	काष्ठा fcpio_host_req *desc = wq->ring.descs;
	वापस &desc[wq->to_use_index];
पूर्ण

अटल अंतरभूत व्योम vnic_wq_copy_post(काष्ठा vnic_wq_copy *wq)
अणु

	((wq->to_use_index + 1) == wq->ring.desc_count) ?
		(wq->to_use_index = 0) : (wq->to_use_index++);
	wq->ring.desc_avail--;

	/* Adding ग_लिखो memory barrier prevents compiler and/or CPU
	 * reordering, thus aव्योमing descriptor posting beक्रमe
	 * descriptor is initialized. Otherwise, hardware can पढ़ो
	 * stale descriptor fields.
	 */
	wmb();

	ioग_लिखो32(wq->to_use_index, &wq->ctrl->posted_index);
पूर्ण

अटल अंतरभूत व्योम vnic_wq_copy_desc_process(काष्ठा vnic_wq_copy *wq, u16 index)
अणु
	अचिन्हित पूर्णांक cnt;

	अगर (wq->to_clean_index <= index)
		cnt = (index - wq->to_clean_index) + 1;
	अन्यथा
		cnt = wq->ring.desc_count - wq->to_clean_index + index + 1;

	wq->to_clean_index = ((index + 1) % wq->ring.desc_count);
	wq->ring.desc_avail += cnt;

पूर्ण

अटल अंतरभूत व्योम vnic_wq_copy_service(काष्ठा vnic_wq_copy *wq,
	u16 completed_index,
	व्योम (*q_service)(काष्ठा vnic_wq_copy *wq,
	काष्ठा fcpio_host_req *wq_desc))
अणु
	काष्ठा fcpio_host_req *wq_desc = wq->ring.descs;
	अचिन्हित पूर्णांक curr_index;

	जबतक (1) अणु

		अगर (q_service)
			(*q_service)(wq, &wq_desc[wq->to_clean_index]);

		wq->ring.desc_avail++;

		curr_index = wq->to_clean_index;

		/* increment the to-clean index so that we start
		 * with an unprocessed index next समय we enter the loop
		 */
		((wq->to_clean_index + 1) == wq->ring.desc_count) ?
			(wq->to_clean_index = 0) : (wq->to_clean_index++);

		अगर (curr_index == completed_index)
			अवरोध;

		/* we have cleaned all the entries */
		अगर ((completed_index == (u16)-1) &&
		    (wq->to_clean_index == wq->to_use_index))
			अवरोध;
	पूर्ण
पूर्ण

व्योम vnic_wq_copy_enable(काष्ठा vnic_wq_copy *wq);
पूर्णांक vnic_wq_copy_disable(काष्ठा vnic_wq_copy *wq);
व्योम vnic_wq_copy_मुक्त(काष्ठा vnic_wq_copy *wq);
पूर्णांक vnic_wq_copy_alloc(काष्ठा vnic_dev *vdev, काष्ठा vnic_wq_copy *wq,
	अचिन्हित पूर्णांक index, अचिन्हित पूर्णांक desc_count, अचिन्हित पूर्णांक desc_size);
व्योम vnic_wq_copy_init(काष्ठा vnic_wq_copy *wq, अचिन्हित पूर्णांक cq_index,
	अचिन्हित पूर्णांक error_पूर्णांकerrupt_enable,
	अचिन्हित पूर्णांक error_पूर्णांकerrupt_offset);
व्योम vnic_wq_copy_clean(काष्ठा vnic_wq_copy *wq,
	व्योम (*q_clean)(काष्ठा vnic_wq_copy *wq,
	काष्ठा fcpio_host_req *wq_desc));

#पूर्ण_अगर /* _VNIC_WQ_COPY_H_ */
