<शैली गुरु>
/*
 * Copyright 2011 Cisco Systems, Inc.  All rights reserved.
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

#अगर_अघोषित _ENIC_PP_H_
#घोषणा _ENIC_PP_H_

#घोषणा ENIC_PP_BY_INDEX(enic, vf, pp, err) \
	करो अणु \
		अगर (enic_is_valid_pp_vf(enic, vf, err)) \
			pp = (vf == PORT_SELF_VF) ? enic->pp : enic->pp + vf; \
		अन्यथा \
			pp = शून्य; \
	पूर्ण जबतक (0)

पूर्णांक enic_process_set_pp_request(काष्ठा enic *enic, पूर्णांक vf,
	काष्ठा enic_port_profile *prev_pp, पूर्णांक *restore_pp);
पूर्णांक enic_process_get_pp_request(काष्ठा enic *enic, पूर्णांक vf,
	पूर्णांक request, u16 *response);
पूर्णांक enic_is_valid_pp_vf(काष्ठा enic *enic, पूर्णांक vf, पूर्णांक *err);

#पूर्ण_अगर /* _ENIC_PP_H_ */
