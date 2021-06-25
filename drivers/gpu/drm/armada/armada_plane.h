<शैली गुरु>
#अगर_अघोषित ARMADA_PLANE_H
#घोषणा ARMADA_PLANE_H

काष्ठा armada_plane_state अणु
	काष्ठा drm_plane_state base;
	u32 src_hw;
	u32 dst_yx;
	u32 dst_hw;
	u32 addrs[2][3];
	u16 pitches[3];
	bool पूर्णांकerlace;
पूर्ण;

#घोषणा to_armada_plane_state(st) \
	container_of(st, काष्ठा armada_plane_state, base)
#घोषणा armada_src_hw(state) to_armada_plane_state(state)->src_hw
#घोषणा armada_dst_yx(state) to_armada_plane_state(state)->dst_yx
#घोषणा armada_dst_hw(state) to_armada_plane_state(state)->dst_hw
#घोषणा armada_addr(state, f, p) to_armada_plane_state(state)->addrs[f][p]
#घोषणा armada_pitch(state, n) to_armada_plane_state(state)->pitches[n]

व्योम armada_drm_plane_calc(काष्ठा drm_plane_state *state, u32 addrs[2][3],
	u16 pitches[3], bool पूर्णांकerlaced);
पूर्णांक armada_drm_plane_prepare_fb(काष्ठा drm_plane *plane,
	काष्ठा drm_plane_state *state);
व्योम armada_drm_plane_cleanup_fb(काष्ठा drm_plane *plane,
	काष्ठा drm_plane_state *old_state);
पूर्णांक armada_drm_plane_atomic_check(काष्ठा drm_plane *plane,
	काष्ठा drm_atomic_state *state);
व्योम armada_plane_reset(काष्ठा drm_plane *plane);
काष्ठा drm_plane_state *armada_plane_duplicate_state(काष्ठा drm_plane *plane);
व्योम armada_plane_destroy_state(काष्ठा drm_plane *plane,
				काष्ठा drm_plane_state *state);

पूर्णांक armada_drm_primary_plane_init(काष्ठा drm_device *drm,
	काष्ठा drm_plane *primary);

#पूर्ण_अगर
