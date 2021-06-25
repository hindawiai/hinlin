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
#अगर_अघोषित _VNIC_CQ_COPY_H_
#घोषणा _VNIC_CQ_COPY_H_

#समावेश "fcpio.h"

अटल अंतरभूत अचिन्हित पूर्णांक vnic_cq_copy_service(
	काष्ठा vnic_cq *cq,
	पूर्णांक (*q_service)(काष्ठा vnic_dev *vdev,
			 अचिन्हित पूर्णांक index,
			 काष्ठा fcpio_fw_req *desc),
	अचिन्हित पूर्णांक work_to_करो)

अणु
	काष्ठा fcpio_fw_req *desc;
	अचिन्हित पूर्णांक work_करोne = 0;
	u8 color;

	desc = (काष्ठा fcpio_fw_req *)((u8 *)cq->ring.descs +
		cq->ring.desc_size * cq->to_clean);
	fcpio_color_dec(desc, &color);

	जबतक (color != cq->last_color) अणु

		अगर ((*q_service)(cq->vdev, cq->index, desc))
			अवरोध;

		cq->to_clean++;
		अगर (cq->to_clean == cq->ring.desc_count) अणु
			cq->to_clean = 0;
			cq->last_color = cq->last_color ? 0 : 1;
		पूर्ण

		desc = (काष्ठा fcpio_fw_req *)((u8 *)cq->ring.descs +
			cq->ring.desc_size * cq->to_clean);
		fcpio_color_dec(desc, &color);

		work_करोne++;
		अगर (work_करोne >= work_to_करो)
			अवरोध;
	पूर्ण

	वापस work_करोne;
पूर्ण

#पूर्ण_अगर /* _VNIC_CQ_COPY_H_ */
