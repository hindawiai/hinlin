<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Atlantic Network Driver
 * Copyright (C) 2020 Marvell International Ltd.
 */

#अगर_अघोषित __MACSEC_API_H__
#घोषणा __MACSEC_API_H__

#समावेश "aq_hw.h"
#समावेश "macsec_struct.h"

#घोषणा NUMROWS_INGRESSPRECTLFRECORD 24
#घोषणा ROWOFFSET_INGRESSPRECTLFRECORD 0

#घोषणा NUMROWS_INGRESSPRECLASSRECORD 48
#घोषणा ROWOFFSET_INGRESSPRECLASSRECORD 0

#घोषणा NUMROWS_INGRESSPOSTCLASSRECORD 48
#घोषणा ROWOFFSET_INGRESSPOSTCLASSRECORD 0

#घोषणा NUMROWS_INGRESSSCRECORD 32
#घोषणा ROWOFFSET_INGRESSSCRECORD 0

#घोषणा NUMROWS_INGRESSSARECORD 32
#घोषणा ROWOFFSET_INGRESSSARECORD 32

#घोषणा NUMROWS_INGRESSSAKEYRECORD 32
#घोषणा ROWOFFSET_INGRESSSAKEYRECORD 0

#घोषणा NUMROWS_INGRESSPOSTCTLFRECORD 24
#घोषणा ROWOFFSET_INGRESSPOSTCTLFRECORD 0

#घोषणा NUMROWS_EGRESSCTLFRECORD 24
#घोषणा ROWOFFSET_EGRESSCTLFRECORD 0

#घोषणा NUMROWS_EGRESSCLASSRECORD 48
#घोषणा ROWOFFSET_EGRESSCLASSRECORD 0

#घोषणा NUMROWS_EGRESSSCRECORD 32
#घोषणा ROWOFFSET_EGRESSSCRECORD 0

#घोषणा NUMROWS_EGRESSSARECORD 32
#घोषणा ROWOFFSET_EGRESSSARECORD 32

#घोषणा NUMROWS_EGRESSSAKEYRECORD 32
#घोषणा ROWOFFSET_EGRESSSAKEYRECORD 96

/*!  Read the raw table data from the specअगरied row of the Egress CTL
 *   Filter table, and unpack it पूर्णांकo the fields of rec.
 *  rec - [OUT] The raw table row data will be unpacked पूर्णांकo the fields of rec.
 *  table_index - The table row to पढ़ो (max 23).
 */
पूर्णांक aq_mss_get_egress_ctlf_record(काष्ठा aq_hw_s *hw,
				  काष्ठा aq_mss_egress_ctlf_record *rec,
				  u16 table_index);

/*!  Pack the fields of rec, and ग_लिखो the packed data पूर्णांकo the
 *   specअगरied row of the Egress CTL Filter table.
 *  rec - [IN] The bitfield values to ग_लिखो to the table row.
 *  table_index - The table row to ग_लिखो(max 23).
 */
पूर्णांक aq_mss_set_egress_ctlf_record(काष्ठा aq_hw_s *hw,
				  स्थिर काष्ठा aq_mss_egress_ctlf_record *rec,
				  u16 table_index);

/*!  Read the raw table data from the specअगरied row of the Egress
 *   Packet Classअगरier table, and unpack it पूर्णांकo the fields of rec.
 *  rec - [OUT] The raw table row data will be unpacked पूर्णांकo the fields of rec.
 *  table_index - The table row to पढ़ो (max 47).
 */
पूर्णांक aq_mss_get_egress_class_record(काष्ठा aq_hw_s *hw,
				   काष्ठा aq_mss_egress_class_record *rec,
				   u16 table_index);

/*!  Pack the fields of rec, and ग_लिखो the packed data पूर्णांकo the
 *   specअगरied row of the Egress Packet Classअगरier table.
 *  rec - [IN] The bitfield values to ग_लिखो to the table row.
 *  table_index - The table row to ग_लिखो (max 47).
 */
पूर्णांक aq_mss_set_egress_class_record(काष्ठा aq_hw_s *hw,
				   स्थिर काष्ठा aq_mss_egress_class_record *rec,
				   u16 table_index);

/*!  Read the raw table data from the specअगरied row of the Egress SC
 *   Lookup table, and unpack it पूर्णांकo the fields of rec.
 *  rec - [OUT] The raw table row data will be unpacked पूर्णांकo the fields of rec.
 *  table_index - The table row to पढ़ो (max 31).
 */
पूर्णांक aq_mss_get_egress_sc_record(काष्ठा aq_hw_s *hw,
				काष्ठा aq_mss_egress_sc_record *rec,
				u16 table_index);

/*!  Pack the fields of rec, and ग_लिखो the packed data पूर्णांकo the
 *   specअगरied row of the Egress SC Lookup table.
 *  rec - [IN] The bitfield values to ग_लिखो to the table row.
 *  table_index - The table row to ग_लिखो (max 31).
 */
पूर्णांक aq_mss_set_egress_sc_record(काष्ठा aq_hw_s *hw,
				स्थिर काष्ठा aq_mss_egress_sc_record *rec,
				u16 table_index);

/*!  Read the raw table data from the specअगरied row of the Egress SA
 *   Lookup table, and unpack it पूर्णांकo the fields of rec.
 *  rec - [OUT] The raw table row data will be unpacked पूर्णांकo the fields of rec.
 *  table_index - The table row to पढ़ो (max 31).
 */
पूर्णांक aq_mss_get_egress_sa_record(काष्ठा aq_hw_s *hw,
				काष्ठा aq_mss_egress_sa_record *rec,
				u16 table_index);

/*!  Pack the fields of rec, and ग_लिखो the packed data पूर्णांकo the
 *   specअगरied row of the Egress SA Lookup table.
 *  rec  - [IN] The bitfield values to ग_लिखो to the table row.
 *  table_index - The table row to ग_लिखो (max 31).
 */
पूर्णांक aq_mss_set_egress_sa_record(काष्ठा aq_hw_s *hw,
				स्थिर काष्ठा aq_mss_egress_sa_record *rec,
				u16 table_index);

/*!  Read the raw table data from the specअगरied row of the Egress SA
 *   Key Lookup table, and unpack it पूर्णांकo the fields of rec.
 *  rec - [OUT] The raw table row data will be unpacked पूर्णांकo the fields of rec.
 *  table_index - The table row to पढ़ो (max 31).
 */
पूर्णांक aq_mss_get_egress_sakey_record(काष्ठा aq_hw_s *hw,
				   काष्ठा aq_mss_egress_sakey_record *rec,
				   u16 table_index);

/*!  Pack the fields of rec, and ग_लिखो the packed data पूर्णांकo the
 *   specअगरied row of the Egress SA Key Lookup table.
 *  rec - [IN] The bitfield values to ग_लिखो to the table row.
 *  table_index - The table row to ग_लिखो (max 31).
 */
पूर्णांक aq_mss_set_egress_sakey_record(काष्ठा aq_hw_s *hw,
				   स्थिर काष्ठा aq_mss_egress_sakey_record *rec,
				   u16 table_index);

/*!  Read the raw table data from the specअगरied row of the Ingress
 *   Pre-MACSec CTL Filter table, and unpack it पूर्णांकo the fields of rec.
 *  rec - [OUT] The raw table row data will be unpacked पूर्णांकo the fields of rec.
 *  table_index - The table row to पढ़ो (max 23).
 */
पूर्णांक aq_mss_get_ingress_prectlf_record(काष्ठा aq_hw_s *hw,
				      काष्ठा aq_mss_ingress_prectlf_record *rec,
				      u16 table_index);

/*!  Pack the fields of rec, and ग_लिखो the packed data पूर्णांकo the
 *   specअगरied row of the Ingress Pre-MACSec CTL Filter table.
 *  rec - [IN] The bitfield values to ग_लिखो to the table row.
 *  table_index - The table row to ग_लिखो(max 23).
 */
पूर्णांक aq_mss_set_ingress_prectlf_record(काष्ठा aq_hw_s *hw,
	स्थिर काष्ठा aq_mss_ingress_prectlf_record *rec,
	u16 table_index);

/*!  Read the raw table data from the specअगरied row of the Ingress
 *   Pre-MACSec Packet Classअगरier table, and unpack it पूर्णांकo the fields of rec.
 *  rec - [OUT] The raw table row data will be unpacked पूर्णांकo the fields of rec.
 *  table_index - The table row to पढ़ो (max 47).
 */
पूर्णांक aq_mss_get_ingress_preclass_record(काष्ठा aq_hw_s *hw,
	काष्ठा aq_mss_ingress_preclass_record *rec,
	u16 table_index);

/*!  Pack the fields of rec, and ग_लिखो the packed data पूर्णांकo the
 *   specअगरied row of the Ingress Pre-MACSec Packet Classअगरier table.
 *  rec - [IN] The bitfield values to ग_लिखो to the table row.
 *  table_index - The table row to ग_लिखो(max 47).
 */
पूर्णांक aq_mss_set_ingress_preclass_record(काष्ठा aq_hw_s *hw,
	स्थिर काष्ठा aq_mss_ingress_preclass_record *rec,
	u16 table_index);

/*!  Read the raw table data from the specअगरied row of the Ingress SC
 *   Lookup table, and unpack it पूर्णांकo the fields of rec.
 *  rec - [OUT] The raw table row data will be unpacked पूर्णांकo the fields of rec.
 *  table_index - The table row to पढ़ो (max 31).
 */
पूर्णांक aq_mss_get_ingress_sc_record(काष्ठा aq_hw_s *hw,
				 काष्ठा aq_mss_ingress_sc_record *rec,
				 u16 table_index);

/*!  Pack the fields of rec, and ग_लिखो the packed data पूर्णांकo the
 *   specअगरied row of the Ingress SC Lookup table.
 *  rec - [IN] The bitfield values to ग_लिखो to the table row.
 *  table_index - The table row to ग_लिखो(max 31).
 */
पूर्णांक aq_mss_set_ingress_sc_record(काष्ठा aq_hw_s *hw,
				 स्थिर काष्ठा aq_mss_ingress_sc_record *rec,
				 u16 table_index);

/*!  Read the raw table data from the specअगरied row of the Ingress SA
 *   Lookup table, and unpack it पूर्णांकo the fields of rec.
 *  rec - [OUT] The raw table row data will be unpacked पूर्णांकo the fields of rec.
 *  table_index - The table row to पढ़ो (max 31).
 */
पूर्णांक aq_mss_get_ingress_sa_record(काष्ठा aq_hw_s *hw,
				 काष्ठा aq_mss_ingress_sa_record *rec,
				 u16 table_index);

/*!  Pack the fields of rec, and ग_लिखो the packed data पूर्णांकo the
 *   specअगरied row of the Ingress SA Lookup table.
 *  rec - [IN] The bitfield values to ग_लिखो to the table row.
 *  table_index - The table row to ग_लिखो(max 31).
 */
पूर्णांक aq_mss_set_ingress_sa_record(काष्ठा aq_hw_s *hw,
				 स्थिर काष्ठा aq_mss_ingress_sa_record *rec,
				 u16 table_index);

/*!  Read the raw table data from the specअगरied row of the Ingress SA
 *   Key Lookup table, and unpack it पूर्णांकo the fields of rec.
 *  rec - [OUT] The raw table row data will be unpacked पूर्णांकo the fields of rec.
 *  table_index - The table row to पढ़ो (max 31).
 */
पूर्णांक aq_mss_get_ingress_sakey_record(काष्ठा aq_hw_s *hw,
				    काष्ठा aq_mss_ingress_sakey_record *rec,
				    u16 table_index);

/*!  Pack the fields of rec, and ग_लिखो the packed data पूर्णांकo the
 *   specअगरied row of the Ingress SA Key Lookup table.
 *  rec - [IN] The bitfield values to ग_लिखो to the table row.
 *  table_index - The table row to ग_लिखो(max 31).
 */
पूर्णांक aq_mss_set_ingress_sakey_record(काष्ठा aq_hw_s *hw,
	स्थिर काष्ठा aq_mss_ingress_sakey_record *rec,
	u16 table_index);

/*!  Read the raw table data from the specअगरied row of the Ingress
 *   Post-MACSec Packet Classअगरier table, and unpack it पूर्णांकo the
 *   fields of rec.
 *  rec - [OUT] The raw table row data will be unpacked पूर्णांकo the fields of rec.
 *  table_index - The table row to पढ़ो (max 48).
 */
पूर्णांक aq_mss_get_ingress_postclass_record(काष्ठा aq_hw_s *hw,
	काष्ठा aq_mss_ingress_postclass_record *rec,
	u16 table_index);

/*!  Pack the fields of rec, and ग_लिखो the packed data पूर्णांकo the
 *   specअगरied row of the Ingress Post-MACSec Packet Classअगरier table.
 *  rec - [IN] The bitfield values to ग_लिखो to the table row.
 *  table_index - The table row to ग_लिखो(max 48).
 */
पूर्णांक aq_mss_set_ingress_postclass_record(काष्ठा aq_hw_s *hw,
	स्थिर काष्ठा aq_mss_ingress_postclass_record *rec,
	u16 table_index);

/*!  Read the raw table data from the specअगरied row of the Ingress
 *   Post-MACSec CTL Filter table, and unpack it पूर्णांकo the fields of rec.
 *  rec - [OUT] The raw table row data will be unpacked पूर्णांकo the fields of rec.
 *  table_index - The table row to पढ़ो (max 23).
 */
पूर्णांक aq_mss_get_ingress_postctlf_record(काष्ठा aq_hw_s *hw,
	काष्ठा aq_mss_ingress_postctlf_record *rec,
	u16 table_index);

/*!  Pack the fields of rec, and ग_लिखो the packed data पूर्णांकo the
 *   specअगरied row of the Ingress Post-MACSec CTL Filter table.
 *  rec - [IN] The bitfield values to ग_लिखो to the table row.
 *  table_index - The table row to ग_लिखो(max 23).
 */
पूर्णांक aq_mss_set_ingress_postctlf_record(काष्ठा aq_hw_s *hw,
	स्थिर काष्ठा aq_mss_ingress_postctlf_record *rec,
	u16 table_index);

/*!  Read the counters क्रम the specअगरied SC, and unpack them पूर्णांकo the
 *   fields of counters.
 *  counters - [OUT] The raw table row data will be unpacked here.
 *  sc_index - The table row to पढ़ो (max 31).
 */
पूर्णांक aq_mss_get_egress_sc_counters(काष्ठा aq_hw_s *hw,
				  काष्ठा aq_mss_egress_sc_counters *counters,
				  u16 sc_index);

/*!  Read the counters क्रम the specअगरied SA, and unpack them पूर्णांकo the
 *   fields of counters.
 *  counters - [OUT] The raw table row data will be unpacked here.
 *  sa_index - The table row to पढ़ो (max 31).
 */
पूर्णांक aq_mss_get_egress_sa_counters(काष्ठा aq_hw_s *hw,
				  काष्ठा aq_mss_egress_sa_counters *counters,
				  u16 sa_index);

/*!  Read the counters क्रम the common egress counters, and unpack them
 *   पूर्णांकo the fields of counters.
 *  counters - [OUT] The raw table row data will be unpacked here.
 */
पूर्णांक aq_mss_get_egress_common_counters(काष्ठा aq_hw_s *hw,
	काष्ठा aq_mss_egress_common_counters *counters);

/*!  Clear all Egress counters to 0.*/
पूर्णांक aq_mss_clear_egress_counters(काष्ठा aq_hw_s *hw);

/*!  Read the counters क्रम the specअगरied SA, and unpack them पूर्णांकo the
 *   fields of counters.
 *  counters - [OUT] The raw table row data will be unpacked here.
 *  sa_index - The table row to पढ़ो (max 31).
 */
पूर्णांक aq_mss_get_ingress_sa_counters(काष्ठा aq_hw_s *hw,
				   काष्ठा aq_mss_ingress_sa_counters *counters,
				   u16 sa_index);

/*!  Read the counters क्रम the common ingress counters, and unpack them
 *   पूर्णांकo the fields of counters.
 *  counters - [OUT] The raw table row data will be unpacked here.
 */
पूर्णांक aq_mss_get_ingress_common_counters(काष्ठा aq_hw_s *hw,
	काष्ठा aq_mss_ingress_common_counters *counters);

/*!  Clear all Ingress counters to 0. */
पूर्णांक aq_mss_clear_ingress_counters(काष्ठा aq_hw_s *hw);

/*!  Get Egress SA expired. */
पूर्णांक aq_mss_get_egress_sa_expired(काष्ठा aq_hw_s *hw, u32 *expired);
/*!  Get Egress SA threshold expired. */
पूर्णांक aq_mss_get_egress_sa_threshold_expired(काष्ठा aq_hw_s *hw,
					   u32 *expired);
/*!  Set Egress SA expired. */
पूर्णांक aq_mss_set_egress_sa_expired(काष्ठा aq_hw_s *hw, u32 expired);
/*!  Set Egress SA threshold expired. */
पूर्णांक aq_mss_set_egress_sa_threshold_expired(काष्ठा aq_hw_s *hw,
					   u32 expired);

#पूर्ण_अगर /* __MACSEC_API_H__ */
