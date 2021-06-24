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

#अगर_अघोषित _FNIC_FIP_H_
#घोषणा _FNIC_FIP_H_


#घोषणा FCOE_CTLR_START_DELAY    2000    /* ms after first adv. to choose FCF */
#घोषणा FCOE_CTLR_FIPVLAN_TOV    2000    /* ms after FIP VLAN disc */
#घोषणा FCOE_CTLR_MAX_SOL        8

#घोषणा FINC_MAX_FLOGI_REJECTS   8

काष्ठा vlan अणु
	__be16 vid;
	__be16 type;
पूर्ण;

/*
 * VLAN entry.
 */
काष्ठा fcoe_vlan अणु
	काष्ठा list_head list;
	u16 vid;		/* vlan ID */
	u16 sol_count;		/* no. of sols sent */
	u16 state;		/* state */
पूर्ण;

क्रमागत fip_vlan_state अणु
	FIP_VLAN_AVAIL  = 0,	/* करोn't करो anything */
	FIP_VLAN_SENT   = 1,	/* sent */
	FIP_VLAN_USED   = 2,	/* succeed */
	FIP_VLAN_FAILED = 3,	/* failed to response */
पूर्ण;

काष्ठा fip_vlan अणु
	काष्ठा ethhdr eth;
	काष्ठा fip_header fip;
	काष्ठा अणु
		काष्ठा fip_mac_desc mac;
		काष्ठा fip_wwn_desc wwnn;
	पूर्ण desc;
पूर्ण;

#पूर्ण_अगर  /* __FINC_FIP_H_ */
