<शैली गुरु>
/*
 * Copyright (c) 2012-2016 VMware, Inc.  All rights reserved.
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of EITHER the GNU General Public License
 * version 2 as published by the Free Software Foundation or the BSD
 * 2-Clause License. This program is distributed in the hope that it
 * will be useful, but WITHOUT ANY WARRANTY; WITHOUT EVEN THE IMPLIED
 * WARRANTY OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License version 2 क्रम more details at
 * http://www.gnu.org/licenses/old-licenses/gpl-2.0.en.hपंचांगl.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program available in the file COPYING in the मुख्य
 * directory of this source tree.
 *
 * The BSD 2-Clause License
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT,
 * INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#समावेश <linux/list.h>

#समावेश "pvrdma.h"

#घोषणा PVRDMA_CMD_TIMEOUT	10000 /* ms */

अटल अंतरभूत पूर्णांक pvrdma_cmd_recv(काष्ठा pvrdma_dev *dev,
				  जोड़ pvrdma_cmd_resp *resp,
				  अचिन्हित resp_code)
अणु
	पूर्णांक err;

	dev_dbg(&dev->pdev->dev, "receive response from device\n");

	err = रुको_क्रम_completion_पूर्णांकerruptible_समयout(&dev->cmd_करोne,
			msecs_to_jअगरfies(PVRDMA_CMD_TIMEOUT));
	अगर (err == 0 || err == -ERESTARTSYS) अणु
		dev_warn(&dev->pdev->dev,
			 "completion timeout or interrupted\n");
		वापस -ETIMEDOUT;
	पूर्ण

	spin_lock(&dev->cmd_lock);
	स_नकल(resp, dev->resp_slot, माप(*resp));
	spin_unlock(&dev->cmd_lock);

	अगर (resp->hdr.ack != resp_code) अणु
		dev_warn(&dev->pdev->dev,
			 "unknown response %#x expected %#x\n",
			 resp->hdr.ack, resp_code);
		वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक
pvrdma_cmd_post(काष्ठा pvrdma_dev *dev, जोड़ pvrdma_cmd_req *req,
		जोड़ pvrdma_cmd_resp *resp, अचिन्हित resp_code)
अणु
	पूर्णांक err;

	dev_dbg(&dev->pdev->dev, "post request to device\n");

	/* Serializiation */
	करोwn(&dev->cmd_sema);

	BUILD_BUG_ON(माप(जोड़ pvrdma_cmd_req) !=
		     माप(काष्ठा pvrdma_cmd_modअगरy_qp));

	spin_lock(&dev->cmd_lock);
	स_नकल(dev->cmd_slot, req, माप(*req));
	spin_unlock(&dev->cmd_lock);

	init_completion(&dev->cmd_करोne);
	pvrdma_ग_लिखो_reg(dev, PVRDMA_REG_REQUEST, 0);

	/* Make sure the request is written beक्रमe पढ़ोing status. */
	mb();

	err = pvrdma_पढ़ो_reg(dev, PVRDMA_REG_ERR);
	अगर (err == 0) अणु
		अगर (resp != शून्य)
			err = pvrdma_cmd_recv(dev, resp, resp_code);
	पूर्ण अन्यथा अणु
		dev_warn(&dev->pdev->dev,
			 "failed to write request error reg: %d\n", err);
		err = -EFAULT;
	पूर्ण

	up(&dev->cmd_sema);

	वापस err;
पूर्ण
