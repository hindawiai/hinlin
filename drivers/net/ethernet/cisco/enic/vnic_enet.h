<शैली गुरु>
/*
 * Copyright 2008-2010 Cisco Systems, Inc.  All rights reserved.
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
 *
 */

#अगर_अघोषित _VNIC_ENIC_H_
#घोषणा _VNIC_ENIC_H_

/* Device-specअगरic region: enet configuration */
काष्ठा vnic_enet_config अणु
	u32 flags;
	u32 wq_desc_count;
	u32 rq_desc_count;
	u16 mtu;
	u16 पूर्णांकr_समयr_deprecated;
	u8 पूर्णांकr_समयr_type;
	u8 पूर्णांकr_mode;
	अक्षर devname[16];
	u32 पूर्णांकr_समयr_usec;
	u16 loop_tag;
	u16 vf_rq_count;
	u16 num_arfs;
पूर्ण;

#घोषणा VENETF_TSO		0x1	/* TSO enabled */
#घोषणा VENETF_LRO		0x2	/* LRO enabled */
#घोषणा VENETF_RXCSUM		0x4	/* RX csum enabled */
#घोषणा VENETF_TXCSUM		0x8	/* TX csum enabled */
#घोषणा VENETF_RSS		0x10	/* RSS enabled */
#घोषणा VENETF_RSSHASH_IPV4	0x20	/* Hash on IPv4 fields */
#घोषणा VENETF_RSSHASH_TCPIPV4	0x40	/* Hash on TCP + IPv4 fields */
#घोषणा VENETF_RSSHASH_IPV6	0x80	/* Hash on IPv6 fields */
#घोषणा VENETF_RSSHASH_TCPIPV6	0x100	/* Hash on TCP + IPv6 fields */
#घोषणा VENETF_RSSHASH_IPV6_EX	0x200	/* Hash on IPv6 extended fields */
#घोषणा VENETF_RSSHASH_TCPIPV6_EX 0x400	/* Hash on TCP + IPv6 ext. fields */
#घोषणा VENETF_LOOP		0x800	/* Loopback enabled */
#घोषणा VENETF_VXLAN		0x10000	/* VxLAN offload */

#घोषणा VENET_INTR_TYPE_MIN	0	/* Timer specs min पूर्णांकerrupt spacing */
#घोषणा VENET_INTR_TYPE_IDLE	1	/* Timer specs idle समय beक्रमe irq */

#घोषणा VENET_INTR_MODE_ANY	0	/* Try MSI-X, then MSI, then INTx */
#घोषणा VENET_INTR_MODE_MSI	1	/* Try MSI then INTx */
#घोषणा VENET_INTR_MODE_INTX	2	/* Try INTx only */

#पूर्ण_अगर /* _VNIC_ENIC_H_ */
