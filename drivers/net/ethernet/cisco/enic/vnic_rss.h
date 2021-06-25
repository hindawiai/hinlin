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
 */

#अगर_अघोषित _VNIC_RSS_H_
#घोषणा _VNIC_RSS_H_

/* RSS key array */

#घोषणा ENIC_RSS_BYTES_PER_KEY	10
#घोषणा ENIC_RSS_KEYS		4
#घोषणा ENIC_RSS_LEN		(ENIC_RSS_BYTES_PER_KEY * ENIC_RSS_KEYS)

जोड़ vnic_rss_key अणु
	काष्ठा अणु
		u8 b[ENIC_RSS_BYTES_PER_KEY];
		u8 b_pad[6];
	पूर्ण key[ENIC_RSS_KEYS];
	u64 raw[8];
पूर्ण;

/* RSS cpu array */
जोड़ vnic_rss_cpu अणु
	काष्ठा अणु
		u8 b[4] ;
		u8 b_pad[4];
	पूर्ण cpu[32];
	u64 raw[32];
पूर्ण;

#पूर्ण_अगर /* _VNIC_RSS_H_ */
