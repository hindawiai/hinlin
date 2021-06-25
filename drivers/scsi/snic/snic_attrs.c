<शैली गुरु>
/*
 * Copyright 2014 Cisco Systems, Inc.  All rights reserved.
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

#समावेश "snic.h"

अटल sमाप_प्रकार
snic_show_sym_name(काष्ठा device *dev,
		काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	काष्ठा snic *snic = shost_priv(class_to_shost(dev));

	वापस snम_लिखो(buf, PAGE_SIZE, "%s\n", snic->name);
पूर्ण

अटल sमाप_प्रकार
snic_show_state(काष्ठा device *dev,
		काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	काष्ठा snic *snic = shost_priv(class_to_shost(dev));

	वापस snम_लिखो(buf, PAGE_SIZE, "%s\n",
			snic_state_str[snic_get_state(snic)]);
पूर्ण

अटल sमाप_प्रकार
snic_show_drv_version(काष्ठा device *dev,
		      काष्ठा device_attribute *attr,
		      अक्षर *buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, "%s\n", SNIC_DRV_VERSION);
पूर्ण

अटल sमाप_प्रकार
snic_show_link_state(काष्ठा device *dev,
		     काष्ठा device_attribute *attr,
		     अक्षर *buf)
अणु
	काष्ठा snic *snic = shost_priv(class_to_shost(dev));

	अगर (snic->config.xpt_type == SNIC_DAS)
		snic->link_status = svnic_dev_link_status(snic->vdev);

	वापस snम_लिखो(buf, PAGE_SIZE, "%s\n",
			(snic->link_status) ? "Link Up" : "Link Down");
पूर्ण

अटल DEVICE_ATTR(snic_sym_name, S_IRUGO, snic_show_sym_name, शून्य);
अटल DEVICE_ATTR(snic_state, S_IRUGO, snic_show_state, शून्य);
अटल DEVICE_ATTR(drv_version, S_IRUGO, snic_show_drv_version, शून्य);
अटल DEVICE_ATTR(link_state, S_IRUGO, snic_show_link_state, शून्य);

काष्ठा device_attribute *snic_attrs[] = अणु
	&dev_attr_snic_sym_name,
	&dev_attr_snic_state,
	&dev_attr_drv_version,
	&dev_attr_link_state,
	शून्य,
पूर्ण;
