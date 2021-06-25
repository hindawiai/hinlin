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

#अगर_अघोषित _VNIC_SNIC_H_
#घोषणा _VNIC_SNIC_H_

#घोषणा VNIC_SNIC_WQ_DESCS_MIN              64
#घोषणा VNIC_SNIC_WQ_DESCS_MAX              1024

#घोषणा VNIC_SNIC_MAXDATAFIELDSIZE_MIN      256
#घोषणा VNIC_SNIC_MAXDATAFIELDSIZE_MAX      2112

#घोषणा VNIC_SNIC_IO_THROTTLE_COUNT_MIN     1
#घोषणा VNIC_SNIC_IO_THROTTLE_COUNT_MAX     1024

#घोषणा VNIC_SNIC_PORT_DOWN_TIMEOUT_MIN     0
#घोषणा VNIC_SNIC_PORT_DOWN_TIMEOUT_MAX     240000

#घोषणा VNIC_SNIC_PORT_DOWN_IO_RETRIES_MIN  0
#घोषणा VNIC_SNIC_PORT_DOWN_IO_RETRIES_MAX  255

#घोषणा VNIC_SNIC_LUNS_PER_TARGET_MIN       1
#घोषणा VNIC_SNIC_LUNS_PER_TARGET_MAX       1024

/* Device-specअगरic region: scsi configuration */
काष्ठा vnic_snic_config अणु
	u32 flags;
	u32 wq_enet_desc_count;
	u32 io_throttle_count;
	u32 port_करोwn_समयout;
	u32 port_करोwn_io_retries;
	u32 luns_per_tgt;
	u16 maxdatafieldsize;
	u16 पूर्णांकr_समयr;
	u8 पूर्णांकr_समयr_type;
	u8 _resvd2;
	u8 xpt_type;
	u8 hid;
पूर्ण;
#पूर्ण_अगर /* _VNIC_SNIC_H_ */
