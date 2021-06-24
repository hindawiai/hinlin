<शैली गुरु>
/**
 * Copyright 2013 Cisco Systems, Inc.  All rights reserved.
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
 *
 */

#अगर_अघोषित __ENIC_API_H__
#घोषणा __ENIC_API_H__

#समावेश <linux/netdevice.h>

#समावेश "vnic_dev.h"
#समावेश "vnic_devcmd.h"

पूर्णांक enic_api_devcmd_proxy_by_index(काष्ठा net_device *netdev, पूर्णांक vf,
	क्रमागत vnic_devcmd_cmd cmd, u64 *a0, u64 *a1, पूर्णांक रुको);

#पूर्ण_अगर
