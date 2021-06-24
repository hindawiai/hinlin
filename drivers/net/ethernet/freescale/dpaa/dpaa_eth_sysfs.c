<शैली गुरु>
/* Copyright 2008-2016 Freescale Semiconductor Inc.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *	 notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary क्रमm must reproduce the above copyright
 *	 notice, this list of conditions and the following disclaimer in the
 *	 करोcumentation and/or other materials provided with the distribution.
 *     * Neither the name of Freescale Semiconductor nor the
 *	 names of its contributors may be used to enकरोrse or promote products
 *	 derived from this software without specअगरic prior written permission.
 *
 *
 * ALTERNATIVELY, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") as published by the Free Software
 * Foundation, either version 2 of that License or (at your option) any
 * later version.
 *
 * THIS SOFTWARE IS PROVIDED BY Freescale Semiconductor ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL Freescale Semiconductor BE LIABLE FOR ANY
 * सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/पन.स>
#समावेश <linux/of_net.h>
#समावेश "dpaa_eth.h"
#समावेश "mac.h"

अटल sमाप_प्रकार dpaa_eth_show_addr(काष्ठा device *dev,
				  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा dpaa_priv *priv = netdev_priv(to_net_dev(dev));
	काष्ठा mac_device *mac_dev = priv->mac_dev;

	अगर (mac_dev)
		वापस प्र_लिखो(buf, "%llx",
				(अचिन्हित दीर्घ दीर्घ)mac_dev->res->start);
	अन्यथा
		वापस प्र_लिखो(buf, "none");
पूर्ण

अटल sमाप_प्रकार dpaa_eth_show_fqids(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा dpaa_priv *priv = netdev_priv(to_net_dev(dev));
	काष्ठा dpaa_fq *prev = शून्य;
	अक्षर *prevstr = शून्य;
	काष्ठा dpaa_fq *पंचांगp;
	काष्ठा dpaa_fq *fq;
	u32 first_fqid = 0;
	u32 last_fqid = 0;
	sमाप_प्रकार bytes = 0;
	अक्षर *str;
	पूर्णांक i = 0;

	list_क्रम_each_entry_safe(fq, पंचांगp, &priv->dpaa_fq_list, list) अणु
		चयन (fq->fq_type) अणु
		हाल FQ_TYPE_RX_DEFAULT:
			str = "Rx default";
			अवरोध;
		हाल FQ_TYPE_RX_ERROR:
			str = "Rx error";
			अवरोध;
		हाल FQ_TYPE_RX_PCD:
			str = "Rx PCD";
			अवरोध;
		हाल FQ_TYPE_TX_CONFIRM:
			str = "Tx default confirmation";
			अवरोध;
		हाल FQ_TYPE_TX_CONF_MQ:
			str = "Tx confirmation (mq)";
			अवरोध;
		हाल FQ_TYPE_TX_ERROR:
			str = "Tx error";
			अवरोध;
		हाल FQ_TYPE_TX:
			str = "Tx";
			अवरोध;
		शेष:
			str = "Unknown";
		पूर्ण

		अगर (prev && (असल(fq->fqid - prev->fqid) != 1 ||
			     str != prevstr)) अणु
			अगर (last_fqid == first_fqid)
				bytes += प्र_लिखो(buf + bytes,
					"%s: %d\n", prevstr, prev->fqid);
			अन्यथा
				bytes += प्र_लिखो(buf + bytes,
					"%s: %d - %d\n", prevstr,
					first_fqid, last_fqid);
		पूर्ण

		अगर (prev && असल(fq->fqid - prev->fqid) == 1 &&
		    str == prevstr) अणु
			last_fqid = fq->fqid;
		पूर्ण अन्यथा अणु
			first_fqid = fq->fqid;
			last_fqid = fq->fqid;
		पूर्ण

		prev = fq;
		prevstr = str;
		i++;
	पूर्ण

	अगर (prev) अणु
		अगर (last_fqid == first_fqid)
			bytes += प्र_लिखो(buf + bytes, "%s: %d\n", prevstr,
					prev->fqid);
		अन्यथा
			bytes += प्र_लिखो(buf + bytes, "%s: %d - %d\n", prevstr,
					first_fqid, last_fqid);
	पूर्ण

	वापस bytes;
पूर्ण

अटल sमाप_प्रकार dpaa_eth_show_bpids(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा dpaa_priv *priv = netdev_priv(to_net_dev(dev));
	sमाप_प्रकार bytes = 0;

	bytes += snम_लिखो(buf + bytes, PAGE_SIZE - bytes, "%u\n",
				  priv->dpaa_bp->bpid);

	वापस bytes;
पूर्ण

अटल काष्ठा device_attribute dpaa_eth_attrs[] = अणु
	__ATTR(device_addr, 0444, dpaa_eth_show_addr, शून्य),
	__ATTR(fqids, 0444, dpaa_eth_show_fqids, शून्य),
	__ATTR(bpids, 0444, dpaa_eth_show_bpids, शून्य),
पूर्ण;

व्योम dpaa_eth_sysfs_init(काष्ठा device *dev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(dpaa_eth_attrs); i++)
		अगर (device_create_file(dev, &dpaa_eth_attrs[i])) अणु
			dev_err(dev, "Error creating sysfs file\n");
			जबतक (i > 0)
				device_हटाओ_file(dev, &dpaa_eth_attrs[--i]);
			वापस;
		पूर्ण
पूर्ण

व्योम dpaa_eth_sysfs_हटाओ(काष्ठा device *dev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(dpaa_eth_attrs); i++)
		device_हटाओ_file(dev, &dpaa_eth_attrs[i]);
पूर्ण
