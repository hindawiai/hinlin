<शैली गुरु>
/*
 * AMD 10Gb Ethernet driver
 *
 * This file is available to you under your choice of the following two
 * licenses:
 *
 * License 1: GPLv2
 *
 * Copyright (c) 2014 Advanced Micro Devices, Inc.
 *
 * This file is मुक्त software; you may copy, redistribute and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or (at
 * your option) any later version.
 *
 * This file is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * This file incorporates work covered by the following copyright and
 * permission notice:
 *     The Synopsys DWC ETHER XGMAC Software Driver and करोcumentation
 *     (hereinafter "Software") is an unsupported proprietary work of Synopsys,
 *     Inc. unless otherwise expressly agreed to in writing between Synopsys
 *     and you.
 *
 *     The Software IS NOT an item of Licensed Software or Licensed Product
 *     under any End User Software License Agreement or Agreement क्रम Licensed
 *     Product with Synopsys or any supplement thereto.  Permission is hereby
 *     granted, मुक्त of अक्षरge, to any person obtaining a copy of this software
 *     annotated with this license and the Software, to deal in the Software
 *     without restriction, including without limitation the rights to use,
 *     copy, modअगरy, merge, publish, distribute, sublicense, and/or sell copies
 *     of the Software, and to permit persons to whom the Software is furnished
 *     to करो so, subject to the following conditions:
 *
 *     The above copyright notice and this permission notice shall be included
 *     in all copies or substantial portions of the Software.
 *
 *     THIS SOFTWARE IS BEING DISTRIBUTED BY SYNOPSYS SOLELY ON AN "AS IS"
 *     BASIS AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 *     TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 *     PARTICULAR PURPOSE ARE HEREBY DISCLAIMED. IN NO EVENT SHALL SYNOPSYS
 *     BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *     CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *     SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *     INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *     CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *     ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 *     THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 * License 2: Modअगरied BSD
 *
 * Copyright (c) 2014 Advanced Micro Devices, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary क्रमm must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       करोcumentation and/or other materials provided with the distribution.
 *     * Neither the name of Advanced Micro Devices, Inc. nor the
 *       names of its contributors may be used to enकरोrse or promote products
 *       derived from this software without specअगरic prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
 * सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * This file incorporates work covered by the following copyright and
 * permission notice:
 *     The Synopsys DWC ETHER XGMAC Software Driver and करोcumentation
 *     (hereinafter "Software") is an unsupported proprietary work of Synopsys,
 *     Inc. unless otherwise expressly agreed to in writing between Synopsys
 *     and you.
 *
 *     The Software IS NOT an item of Licensed Software or Licensed Product
 *     under any End User Software License Agreement or Agreement क्रम Licensed
 *     Product with Synopsys or any supplement thereto.  Permission is hereby
 *     granted, मुक्त of अक्षरge, to any person obtaining a copy of this software
 *     annotated with this license and the Software, to deal in the Software
 *     without restriction, including without limitation the rights to use,
 *     copy, modअगरy, merge, publish, distribute, sublicense, and/or sell copies
 *     of the Software, and to permit persons to whom the Software is furnished
 *     to करो so, subject to the following conditions:
 *
 *     The above copyright notice and this permission notice shall be included
 *     in all copies or substantial portions of the Software.
 *
 *     THIS SOFTWARE IS BEING DISTRIBUTED BY SYNOPSYS SOLELY ON AN "AS IS"
 *     BASIS AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 *     TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 *     PARTICULAR PURPOSE ARE HEREBY DISCLAIMED. IN NO EVENT SHALL SYNOPSYS
 *     BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *     CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *     SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *     INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *     CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *     ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 *     THE POSSIBILITY OF SUCH DAMAGE.
 */

#समावेश <linux/debugfs.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>

#समावेश "xgbe.h"
#समावेश "xgbe-common.h"

अटल sमाप_प्रकार xgbe_common_पढ़ो(अक्षर __user *buffer, माप_प्रकार count,
				loff_t *ppos, अचिन्हित पूर्णांक value)
अणु
	अक्षर *buf;
	sमाप_प्रकार len;

	अगर (*ppos != 0)
		वापस 0;

	buf = kaप्र_लिखो(GFP_KERNEL, "0x%08x\n", value);
	अगर (!buf)
		वापस -ENOMEM;

	अगर (count < म_माप(buf)) अणु
		kमुक्त(buf);
		वापस -ENOSPC;
	पूर्ण

	len = simple_पढ़ो_from_buffer(buffer, count, ppos, buf, म_माप(buf));
	kमुक्त(buf);

	वापस len;
पूर्ण

अटल sमाप_प्रकार xgbe_common_ग_लिखो(स्थिर अक्षर __user *buffer, माप_प्रकार count,
				 loff_t *ppos, अचिन्हित पूर्णांक *value)
अणु
	अक्षर workarea[32];
	sमाप_प्रकार len;
	पूर्णांक ret;

	अगर (*ppos != 0)
		वापस -EINVAL;

	अगर (count >= माप(workarea))
		वापस -ENOSPC;

	len = simple_ग_लिखो_to_buffer(workarea, माप(workarea) - 1, ppos,
				     buffer, count);
	अगर (len < 0)
		वापस len;

	workarea[len] = '\0';
	ret = kstrtouपूर्णांक(workarea, 16, value);
	अगर (ret)
		वापस -EIO;

	वापस len;
पूर्ण

अटल sमाप_प्रकार xgmac_reg_addr_पढ़ो(काष्ठा file *filp, अक्षर __user *buffer,
				   माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा xgbe_prv_data *pdata = filp->निजी_data;

	वापस xgbe_common_पढ़ो(buffer, count, ppos, pdata->debugfs_xgmac_reg);
पूर्ण

अटल sमाप_प्रकार xgmac_reg_addr_ग_लिखो(काष्ठा file *filp,
				    स्थिर अक्षर __user *buffer,
				    माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा xgbe_prv_data *pdata = filp->निजी_data;

	वापस xgbe_common_ग_लिखो(buffer, count, ppos,
				 &pdata->debugfs_xgmac_reg);
पूर्ण

अटल sमाप_प्रकार xgmac_reg_value_पढ़ो(काष्ठा file *filp, अक्षर __user *buffer,
				    माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा xgbe_prv_data *pdata = filp->निजी_data;
	अचिन्हित पूर्णांक value;

	value = XGMAC_IOREAD(pdata, pdata->debugfs_xgmac_reg);

	वापस xgbe_common_पढ़ो(buffer, count, ppos, value);
पूर्ण

अटल sमाप_प्रकार xgmac_reg_value_ग_लिखो(काष्ठा file *filp,
				     स्थिर अक्षर __user *buffer,
				     माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा xgbe_prv_data *pdata = filp->निजी_data;
	अचिन्हित पूर्णांक value;
	sमाप_प्रकार len;

	len = xgbe_common_ग_लिखो(buffer, count, ppos, &value);
	अगर (len < 0)
		वापस len;

	XGMAC_IOWRITE(pdata, pdata->debugfs_xgmac_reg, value);

	वापस len;
पूर्ण

अटल स्थिर काष्ठा file_operations xgmac_reg_addr_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = simple_खोलो,
	.पढ़ो =  xgmac_reg_addr_पढ़ो,
	.ग_लिखो = xgmac_reg_addr_ग_लिखो,
पूर्ण;

अटल स्थिर काष्ठा file_operations xgmac_reg_value_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = simple_खोलो,
	.पढ़ो =  xgmac_reg_value_पढ़ो,
	.ग_लिखो = xgmac_reg_value_ग_लिखो,
पूर्ण;

अटल sमाप_प्रकार xpcs_mmd_पढ़ो(काष्ठा file *filp, अक्षर __user *buffer,
			     माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा xgbe_prv_data *pdata = filp->निजी_data;

	वापस xgbe_common_पढ़ो(buffer, count, ppos, pdata->debugfs_xpcs_mmd);
पूर्ण

अटल sमाप_प्रकार xpcs_mmd_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *buffer,
			      माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा xgbe_prv_data *pdata = filp->निजी_data;

	वापस xgbe_common_ग_लिखो(buffer, count, ppos,
				 &pdata->debugfs_xpcs_mmd);
पूर्ण

अटल sमाप_प्रकार xpcs_reg_addr_पढ़ो(काष्ठा file *filp, अक्षर __user *buffer,
				  माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा xgbe_prv_data *pdata = filp->निजी_data;

	वापस xgbe_common_पढ़ो(buffer, count, ppos, pdata->debugfs_xpcs_reg);
पूर्ण

अटल sमाप_प्रकार xpcs_reg_addr_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *buffer,
				   माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा xgbe_prv_data *pdata = filp->निजी_data;

	वापस xgbe_common_ग_लिखो(buffer, count, ppos,
				 &pdata->debugfs_xpcs_reg);
पूर्ण

अटल sमाप_प्रकार xpcs_reg_value_पढ़ो(काष्ठा file *filp, अक्षर __user *buffer,
				   माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा xgbe_prv_data *pdata = filp->निजी_data;
	अचिन्हित पूर्णांक value;

	value = XMDIO_READ(pdata, pdata->debugfs_xpcs_mmd,
			   pdata->debugfs_xpcs_reg);

	वापस xgbe_common_पढ़ो(buffer, count, ppos, value);
पूर्ण

अटल sमाप_प्रकार xpcs_reg_value_ग_लिखो(काष्ठा file *filp,
				    स्थिर अक्षर __user *buffer,
				    माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा xgbe_prv_data *pdata = filp->निजी_data;
	अचिन्हित पूर्णांक value;
	sमाप_प्रकार len;

	len = xgbe_common_ग_लिखो(buffer, count, ppos, &value);
	अगर (len < 0)
		वापस len;

	XMDIO_WRITE(pdata, pdata->debugfs_xpcs_mmd, pdata->debugfs_xpcs_reg,
		    value);

	वापस len;
पूर्ण

अटल स्थिर काष्ठा file_operations xpcs_mmd_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = simple_खोलो,
	.पढ़ो =  xpcs_mmd_पढ़ो,
	.ग_लिखो = xpcs_mmd_ग_लिखो,
पूर्ण;

अटल स्थिर काष्ठा file_operations xpcs_reg_addr_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = simple_खोलो,
	.पढ़ो =  xpcs_reg_addr_पढ़ो,
	.ग_लिखो = xpcs_reg_addr_ग_लिखो,
पूर्ण;

अटल स्थिर काष्ठा file_operations xpcs_reg_value_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = simple_खोलो,
	.पढ़ो =  xpcs_reg_value_पढ़ो,
	.ग_लिखो = xpcs_reg_value_ग_लिखो,
पूर्ण;

अटल sमाप_प्रकार xprop_reg_addr_पढ़ो(काष्ठा file *filp, अक्षर __user *buffer,
				   माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा xgbe_prv_data *pdata = filp->निजी_data;

	वापस xgbe_common_पढ़ो(buffer, count, ppos, pdata->debugfs_xprop_reg);
पूर्ण

अटल sमाप_प्रकार xprop_reg_addr_ग_लिखो(काष्ठा file *filp,
				    स्थिर अक्षर __user *buffer,
				    माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा xgbe_prv_data *pdata = filp->निजी_data;

	वापस xgbe_common_ग_लिखो(buffer, count, ppos,
				 &pdata->debugfs_xprop_reg);
पूर्ण

अटल sमाप_प्रकार xprop_reg_value_पढ़ो(काष्ठा file *filp, अक्षर __user *buffer,
				    माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा xgbe_prv_data *pdata = filp->निजी_data;
	अचिन्हित पूर्णांक value;

	value = XP_IOREAD(pdata, pdata->debugfs_xprop_reg);

	वापस xgbe_common_पढ़ो(buffer, count, ppos, value);
पूर्ण

अटल sमाप_प्रकार xprop_reg_value_ग_लिखो(काष्ठा file *filp,
				     स्थिर अक्षर __user *buffer,
				     माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा xgbe_prv_data *pdata = filp->निजी_data;
	अचिन्हित पूर्णांक value;
	sमाप_प्रकार len;

	len = xgbe_common_ग_लिखो(buffer, count, ppos, &value);
	अगर (len < 0)
		वापस len;

	XP_IOWRITE(pdata, pdata->debugfs_xprop_reg, value);

	वापस len;
पूर्ण

अटल स्थिर काष्ठा file_operations xprop_reg_addr_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = simple_खोलो,
	.पढ़ो =  xprop_reg_addr_पढ़ो,
	.ग_लिखो = xprop_reg_addr_ग_लिखो,
पूर्ण;

अटल स्थिर काष्ठा file_operations xprop_reg_value_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = simple_खोलो,
	.पढ़ो =  xprop_reg_value_पढ़ो,
	.ग_लिखो = xprop_reg_value_ग_लिखो,
पूर्ण;

अटल sमाप_प्रकार xi2c_reg_addr_पढ़ो(काष्ठा file *filp, अक्षर __user *buffer,
				  माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा xgbe_prv_data *pdata = filp->निजी_data;

	वापस xgbe_common_पढ़ो(buffer, count, ppos, pdata->debugfs_xi2c_reg);
पूर्ण

अटल sमाप_प्रकार xi2c_reg_addr_ग_लिखो(काष्ठा file *filp,
				   स्थिर अक्षर __user *buffer,
				   माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा xgbe_prv_data *pdata = filp->निजी_data;

	वापस xgbe_common_ग_लिखो(buffer, count, ppos,
				 &pdata->debugfs_xi2c_reg);
पूर्ण

अटल sमाप_प्रकार xi2c_reg_value_पढ़ो(काष्ठा file *filp, अक्षर __user *buffer,
				   माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा xgbe_prv_data *pdata = filp->निजी_data;
	अचिन्हित पूर्णांक value;

	value = XI2C_IOREAD(pdata, pdata->debugfs_xi2c_reg);

	वापस xgbe_common_पढ़ो(buffer, count, ppos, value);
पूर्ण

अटल sमाप_प्रकार xi2c_reg_value_ग_लिखो(काष्ठा file *filp,
				    स्थिर अक्षर __user *buffer,
				    माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा xgbe_prv_data *pdata = filp->निजी_data;
	अचिन्हित पूर्णांक value;
	sमाप_प्रकार len;

	len = xgbe_common_ग_लिखो(buffer, count, ppos, &value);
	अगर (len < 0)
		वापस len;

	XI2C_IOWRITE(pdata, pdata->debugfs_xi2c_reg, value);

	वापस len;
पूर्ण

अटल स्थिर काष्ठा file_operations xi2c_reg_addr_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = simple_खोलो,
	.पढ़ो =  xi2c_reg_addr_पढ़ो,
	.ग_लिखो = xi2c_reg_addr_ग_लिखो,
पूर्ण;

अटल स्थिर काष्ठा file_operations xi2c_reg_value_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = simple_खोलो,
	.पढ़ो =  xi2c_reg_value_पढ़ो,
	.ग_लिखो = xi2c_reg_value_ग_लिखो,
पूर्ण;

व्योम xgbe_debugfs_init(काष्ठा xgbe_prv_data *pdata)
अणु
	अक्षर *buf;

	/* Set शेषs */
	pdata->debugfs_xgmac_reg = 0;
	pdata->debugfs_xpcs_mmd = 1;
	pdata->debugfs_xpcs_reg = 0;

	buf = kaप्र_लिखो(GFP_KERNEL, "amd-xgbe-%s", pdata->netdev->name);
	अगर (!buf)
		वापस;

	pdata->xgbe_debugfs = debugfs_create_dir(buf, शून्य);

	debugfs_create_file("xgmac_register", 0600, pdata->xgbe_debugfs, pdata,
			    &xgmac_reg_addr_fops);

	debugfs_create_file("xgmac_register_value", 0600, pdata->xgbe_debugfs,
			    pdata, &xgmac_reg_value_fops);

	debugfs_create_file("xpcs_mmd", 0600, pdata->xgbe_debugfs, pdata,
			    &xpcs_mmd_fops);

	debugfs_create_file("xpcs_register", 0600, pdata->xgbe_debugfs, pdata,
			    &xpcs_reg_addr_fops);

	debugfs_create_file("xpcs_register_value", 0600, pdata->xgbe_debugfs,
			    pdata, &xpcs_reg_value_fops);

	अगर (pdata->xprop_regs) अणु
		debugfs_create_file("xprop_register", 0600, pdata->xgbe_debugfs,
				    pdata, &xprop_reg_addr_fops);

		debugfs_create_file("xprop_register_value", 0600,
				    pdata->xgbe_debugfs, pdata,
				    &xprop_reg_value_fops);
	पूर्ण

	अगर (pdata->xi2c_regs) अणु
		debugfs_create_file("xi2c_register", 0600, pdata->xgbe_debugfs,
				    pdata, &xi2c_reg_addr_fops);

		debugfs_create_file("xi2c_register_value", 0600,
				    pdata->xgbe_debugfs, pdata,
				    &xi2c_reg_value_fops);
	पूर्ण

	अगर (pdata->vdata->an_cdr_workaround) अणु
		debugfs_create_bool("an_cdr_workaround", 0600,
				    pdata->xgbe_debugfs,
				    &pdata->debugfs_an_cdr_workaround);

		debugfs_create_bool("an_cdr_track_early", 0600,
				    pdata->xgbe_debugfs,
				    &pdata->debugfs_an_cdr_track_early);
	पूर्ण

	kमुक्त(buf);
पूर्ण

व्योम xgbe_debugfs_निकास(काष्ठा xgbe_prv_data *pdata)
अणु
	debugfs_हटाओ_recursive(pdata->xgbe_debugfs);
	pdata->xgbe_debugfs = शून्य;
पूर्ण

व्योम xgbe_debugfs_नाम(काष्ठा xgbe_prv_data *pdata)
अणु
	अक्षर *buf;

	अगर (!pdata->xgbe_debugfs)
		वापस;

	buf = kaप्र_लिखो(GFP_KERNEL, "amd-xgbe-%s", pdata->netdev->name);
	अगर (!buf)
		वापस;

	अगर (!म_भेद(pdata->xgbe_debugfs->d_name.name, buf))
		जाओ out;

	debugfs_नाम(pdata->xgbe_debugfs->d_parent, pdata->xgbe_debugfs,
		       pdata->xgbe_debugfs->d_parent, buf);

out:
	kमुक्त(buf);
पूर्ण
