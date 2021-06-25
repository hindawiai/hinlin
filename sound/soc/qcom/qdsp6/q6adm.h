<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __Q6_ADM_V2_H__
#घोषणा __Q6_ADM_V2_H__

#घोषणा ADM_PATH_PLAYBACK	0x1
#घोषणा ADM_PATH_LIVE_REC	0x2
#घोषणा MAX_COPPS_PER_PORT	8
#घोषणा शून्य_COPP_TOPOLOGY	0x00010312

/* multiple copp per stream. */
काष्ठा route_payload अणु
	पूर्णांक num_copps;
	पूर्णांक session_id;
	पूर्णांक copp_idx[MAX_COPPS_PER_PORT];
	पूर्णांक port_id[MAX_COPPS_PER_PORT];
पूर्ण;

काष्ठा q6copp;
काष्ठा q6copp *q6adm_खोलो(काष्ठा device *dev, पूर्णांक port_id, पूर्णांक path, पूर्णांक rate,
			   पूर्णांक channel_mode, पूर्णांक topology, पूर्णांक perf_mode,
			   uपूर्णांक16_t bit_width, पूर्णांक app_type, पूर्णांक acdb_id);
पूर्णांक q6adm_बंद(काष्ठा device *dev, काष्ठा q6copp *copp);
पूर्णांक q6adm_get_copp_id(काष्ठा q6copp *copp);
पूर्णांक q6adm_matrix_map(काष्ठा device *dev, पूर्णांक path,
		     काष्ठा route_payload payload_map, पूर्णांक perf_mode);

#पूर्ण_अगर /* __Q6_ADM_V2_H__ */
