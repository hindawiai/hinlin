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
#समावेश <linux/माला.स>
#समावेश <linux/device.h>
#समावेश <scsi/scsi_host.h>
#समावेश "fnic.h"

अटल sमाप_प्रकार fnic_show_state(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा fc_lport *lp = shost_priv(class_to_shost(dev));
	काष्ठा fnic *fnic = lport_priv(lp);

	वापस snम_लिखो(buf, PAGE_SIZE, "%s\n", fnic_state_str[fnic->state]);
पूर्ण

अटल sमाप_प्रकार fnic_show_drv_version(काष्ठा device *dev,
				     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, "%s\n", DRV_VERSION);
पूर्ण

अटल sमाप_प्रकार fnic_show_link_state(काष्ठा device *dev,
				    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा fc_lport *lp = shost_priv(class_to_shost(dev));

	वापस snम_लिखो(buf, PAGE_SIZE, "%s\n", (lp->link_up)
			? "Link Up" : "Link Down");
पूर्ण

अटल DEVICE_ATTR(fnic_state, S_IRUGO, fnic_show_state, शून्य);
अटल DEVICE_ATTR(drv_version, S_IRUGO, fnic_show_drv_version, शून्य);
अटल DEVICE_ATTR(link_state, S_IRUGO, fnic_show_link_state, शून्य);

काष्ठा device_attribute *fnic_attrs[] = अणु
	&dev_attr_fnic_state,
	&dev_attr_drv_version,
	&dev_attr_link_state,
	शून्य,
पूर्ण;
