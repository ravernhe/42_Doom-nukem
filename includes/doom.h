/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravernhe <ravernhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:25:22 by ravernhe          #+#    #+#             */
/*   Updated: 2020/03/09 12:15:28 by ravernhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_H
# define DOOM_H

# include "../libft/includes/libft.h"
# include "SDL2/SDL.h"
# include "SDL2/SDL_mixer.h"
# include "math.h"
# include <pthread.h>
# define SIZE_X 800
# define SIZE_Y 600
# define MSPEED 0.12f
# define SPEED 0.75f
# define RUNSPEED 4.0f
# define NB_THREAD 8

typedef struct		s_mat4x4
{
	float			m[4][4];
}					t_mat4x4;

typedef struct		s_bres
{
	int				x0;
	int				y0;
	int				x1;
	int				y1;
	int				dx;
	int				sx;
	int				dy;
	int				sy;
	int				err;
	int				e2;
}					t_bres;

typedef struct		s_tex_var
{
	int				r;
	int				g;
	int				b;
	int				i;
	int				j;
	int				noc;
	int				dy1;
	int				dx1;
	int				dy2;
	int				dx2;
	float			dv1;
	float			du1;
	float			dw1;
	float			dv2;
	float			du2;
	float			dw2;
	float			tex_u;
	float			tex_v;
	float			tex_w;
	float			dax_step;
	float			dbx_step;
	float			du1_step;
	float			dv1_step;
	float			du2_step;
	float			dv2_step;
	float			dw1_step;
	float			dw2_step;
	int				ax;
	int				bx;
	float			tex_su;
	float			tex_sv;
	float			tex_sw;
	float			tex_eu;
	float			tex_ev;
	float			tex_ew;
	float			tstep;
	float			t;
	int				tex_x;
	int				tex_y;
}					t_tex_var;

typedef struct		s_sdl
{
	SDL_Window		*window;
	SDL_Renderer	*render;
	SDL_Surface		*surface;
	SDL_Texture		*texture;
	SDL_Event		event;
	int				x;
	int				y;

}					t_sdl;

typedef struct		s_mix
{
	Mix_Music		*music;
	Mix_Chunk		*shoot;
	Mix_Chunk		*damage;
	Mix_Chunk		*reload;
	Mix_Chunk		*jump;
	Mix_Chunk		*portal;

}					t_mix;

typedef struct		s_texture
{
	char			*name;
	int				**pixels;
	int				**alphas;
	int				x;
	int				y;
}					t_texture;

typedef struct		s_tex_data
{
	int				nb_color;
	int				cpp;
	char			**dico;
	int				*trad;
	int				*alpha;
	int				index;
}					t_tex_data;

typedef struct		s_vec3d
{
	float			x;
	float			y;
	float			z;
	float			w;
}					t_vec3d;

typedef struct		s_vec2d
{
	float			u;
	float			v;
	float			w;
}					t_vec2d;

typedef struct		s_triangle
{
	t_vec3d			p[3];
	t_vec2d			t[3];
	int				index;
}					t_tri;

typedef struct		s_obb
{
	int				id;
	int				first;
	int				last;
	t_vec3d			center;
	t_vec3d			halfsize;
}					t_obb;

typedef struct		s_aclip
{
	int				nc;
	int				p;
	int				k;
	int				i;
}					t_aclip;

typedef struct		s_mask
{
	uint32_t		r;
	uint32_t		g;
	uint32_t		b;
	uint32_t		a;
}					t_mask;

typedef struct		s_ctri
{
	t_vec3d			in_p[3];
	t_vec3d			out_p[3];
	t_vec2d			in_t[3];
	t_vec2d			out_t[3];
}					t_ctri;

typedef struct		s_clip
{
	int				in_pc;
	int				out_pc;
	int				in_tc;
	int				out_tc;
	float			d0;
	float			d1;
	float			d2;
	float			t;
	t_vec3d			p_p;
	t_vec3d			p_n;
}					t_clip;

typedef struct		s_env
{
	t_tri			*tri;
	t_tri			**tour;
	t_vec3d			vlookdir;
	t_vec3d			vlookright;
	t_vec3d			vcamera;
	t_vec3d			spawn;
	t_vec3d			movement;
	t_mat4x4		matproj;
	int				nb_tri;
	int				nb_tex;
	int				nb_obb;
	int				hp;
	int				r_hp;
	int				nrj;
	int				shoot;
	int				tuto;
	int				dy;
	int				intro;
	int				end;
	int				fin;
	int				noc;
	float			fyaw;
	float			fpitch;
	float			crunch;
	t_texture		*tex;
	t_obb			*obb;
	t_mix			mix;
}					t_env;

typedef struct		s_world
{
	t_mat4x4		matrotz;
	t_mat4x4		matrotx;
	t_mat4x4		mattrans;
	t_mat4x4		matworld;
	t_mat4x4		matcam;
	t_mat4x4		matview;
	t_vec3d			vcam_ray;
	t_vec3d			vup;
	t_vec3d			vtarget;
	t_vec3d			vright;
	t_vec3d			normal;
	int				i;
	int				d;
}					t_world;

typedef struct		s_clipz
{
	int				nclipped;
	int				n;
	t_tri			clipped[2];
	t_vec3d			plane_p;
	t_vec3d			plane_n;
}					t_clipz;

typedef struct		s_vol
{
	float			lon;
	float			lar;
	float			hau;
	float			tmp;
	int				tok[3];
	int				k;
	int				i;
	int				j;
}					t_vol;

typedef struct		s_coll
{
	float			*d_vec;
	t_vec3d			max;
	t_vec3d			min;
	int				ret;
	int				i;
	int				ret2;
}					t_coll;

typedef struct		s_pars
{
	char			*buff;
	int				fd;
	int				ret;
	int				v[2];
	int				m[3];
	int				o[2];
}					t_pars;

typedef struct		s_surf
{
	int				x;
	int				y;
	int				i;
	int				j;
}					t_surf;

typedef struct		s_thvar
{
	t_tri			*n_tri;
	int				ret;
	int				i;
}					t_thvar;

typedef struct		s_hit
{
	t_vec3d			max;
	t_vec3d			min;
	t_vec3d			pmax;
	t_vec3d			pmin;
}					t_hit;

typedef struct		s_depth
{
	int				color;
	float			w;
}					t_depth;

typedef struct		s_draw_worker
{
	t_tri			*tri_proj;
	t_tri			*tmp_tri;
	int				start;
	int				end;
}					t_draw_worker;

typedef struct		s_depth_worker
{
	t_tri			*tri;
	t_texture		*tex;
	t_depth			*depth;
	int				start;
	int				end;
}					t_depth_worker;

typedef struct		s_move
{
	float			velocity;
	float			speed;
	float			gravity;
	float			dy;
	int				jump;
	int				crouch;
	int				fly;
	int				flag;
}					t_move;

typedef struct		s_gevent
{
	const Uint8		*keys;
	t_move			move;
}					t_gevent;

void				init_vec(t_vec3d *v, float x, float y, float z);
void				ft_exit(char *message);
void				ft_init_sdl(t_sdl *sdl);
void				ft_init_mix(t_mix *mix);
void				init_vec(t_vec3d *v, float x, float y, float z);
void				ft_exit(char *message);
void				clean_quit(t_sdl *sdl, t_env *env);
void				get_event(t_sdl *sdl, t_env *env);
void				shoot_tourelle(t_env *env);
void				move_tourelle(t_env *env);
int					hit_player(t_vec3d tir, t_obb *obb, int borne, t_env *env);
void				mouse_cam(t_env *env, t_sdl *sdl);
void				save_tour(t_env *env);
void				anim_port(t_env *env, unsigned int tick);
void				display(t_sdl *sdl, t_env *env);
t_tri				scale_screen(t_tri tri);
void				draw_crosshair(t_sdl *sdl);
t_tri				trans_mat(t_tri tri_trans, t_world *world, t_env *env);
t_tri				world_to_view(t_tri t_trs, t_tri t_vw, t_world world);
t_tri				projection(t_tri tri_proj, t_clipz clipz, t_env *env);
void				texture_portal2(t_obb *obb, t_env *env);
void				texture_portal(t_obb *obb, t_env *env);
void				shoot(t_env *env);
void				init_move(t_move *move);
void				get_move(t_move *move, const Uint8 *keys);
void				physic(t_env *env, t_move *move, const Uint8 *keys);
int					collide_ground(t_obb *obb, t_vec3d cam, int n_o, float spd);
float				cube_volume(t_env *env, t_obb obb);
int					collide(t_env *env, t_vec3d cam, int flag, float speed);
void				init_collide(t_coll *c, int flag, float speed, t_vec3d *ca);
void				move_forw(const Uint8 *k, t_vec3d vf, t_env *en, t_move *m);
void				move_side(const Uint8 *k, t_vec3d vr, t_env *en, t_move *m);
void				init_col(float *data_vec, t_vec3d cent, t_vec3d half);
void				vanish_item(t_env *env, t_obb obb);
float				ft_dist(t_vec3d a, t_vec3d b);
float				cube_greg(t_env *env, t_obb obb);
float				volume_pyr(t_tri tri, t_vec3d cam);
void				crouching(t_env *env, t_move *move, const Uint8 *keys);
void				fly(t_env *env, t_move *move, const Uint8 *keys);
float				get_dist(float *dist, float tmp, float d1, float d2);
float				get_third(float d1, float d2, t_tri tri);
void				init_vol(t_vol *v, t_env *env, int i);
void				calc_vol(t_vol *v, t_env *env, t_obb obb);
void				init_tok_vol(t_vol *v);
void				init_check_slop(t_env *env, t_obb obb, float *v, float *py);
int					return_slope(t_obb obb, float *py, float volume);
int					check_slope(t_env *env, t_vec3d cam, int flag, t_obb obb);
t_vec3d				p_vec(char *str, t_vec3d vec);
t_tri				p_tri(char *str, t_tri tri, t_vec3d *list, t_vec2d *uv);
t_env				parse(char *file_name, t_env env, t_vec3d *lt, t_vec2d *uv);
int					skip(char *str, int i);
t_vec3d				*vec_add_size(t_vec3d *data, int size);
t_tri				*tri_add_size(t_tri *data, int size);
t_tri				*tri_memcpy(t_tri *dest, t_tri *src, size_t n);
t_vec2d				*vec2_add_size(t_vec2d *data, int size);
t_vec2d				p_vec2(char *str, t_vec2d vec);
void				get_tex(t_env *env, char *buff);
void				get_spawn(t_env *env, char *str);
t_obb				*obb_add_size(t_obb *data, int size);
t_obb				p_obb(t_obb obb, t_tri *tri, int nb, int first);
t_vec3d				*get_vec(t_pars *p, t_vec3d *list, char *buff);
t_vec2d				*get_vec_tex(t_pars *p, t_vec2d *uv, char *buff);
void				get_face(t_env *env, t_pars *p, t_vec3d *list, t_vec2d *uv);
void				get_obb(t_env *env, t_pars *p);
t_env				end_pars(t_env *env, t_vec3d *list, t_vec2d *uv, t_pars *p);
void				init_bres(t_vec3d v0, t_vec3d v1, t_bres *bres);
void				drawline(t_vec3d v0, t_vec3d v1, t_sdl *sdl);
t_surf				fill_surf_struct(int x, int y, int i, int j);
void				surf_render(t_sdl *sdl, SDL_Surface *surface, t_surf s);
void				fill_surface(SDL_Surface *suf, t_texture tex, int x, int y);
void				draw_hud(t_sdl *sdl, t_env *env);
void				draw_intro(t_sdl *sdl, t_env *env);
void				draw_stuff(t_sdl *sdl, t_env *env);
void				check_tex_size(t_env *env);
void				draw_weapon(t_sdl *sdl, t_env *env);
void				swap_v(t_vec3d *v1, t_vec3d *v2);
void				swap_v2(t_vec2d *v1, t_vec2d *v2);
void				swap_f(float *v1, float *v2);
void				swap_t(t_tri *t1, t_tri *t2);
void				swap_i(int *v1, int *v2);
void				tri_to_pixel(t_sdl *sdl, t_tri *tri_pj, int d, t_env *env);
void				init_plane(t_vec3d *plane);
int					clip_all_plane(int p, t_vec3d *pla, t_tri tmp_i, t_tri *cd);
void				new_clip_tri(t_aclip *ac, t_tri *clipped, t_tri *cpy_tri);
t_tri				*alloc_tri(t_tri *tmp_tri, int d, t_tri *cpy_tri);
t_tri				*do_thread(t_tri *tri_proj, int *d, int nb_thread);
t_tri				*tri_mem_join(t_tri *dest, t_tri *src, int start, int end);
t_tri				*after_clip(t_tri *tri_proj, int start, int *end);
t_vec3d				vec_add(t_vec3d v1, t_vec3d v2);
t_vec3d				vec_sub(t_vec3d v1, t_vec3d v2);
t_vec3d				vec_mul(t_vec3d v1, float k);
t_vec3d				vec_div(t_vec3d v1, float k);
float				dot_product(t_vec3d v1, t_vec3d v2);
float				vec_len(t_vec3d v1);
t_vec3d				vec_normalise(t_vec3d v1);
t_vec3d				cross_product(t_vec3d v1, t_vec3d v2);
t_vec3d				calc_normal(t_vec3d normal, t_tri tri_trans);
void				init_mat_zero(t_mat4x4 *mat);
t_mat4x4			init_matrotx(float ftheta);
t_mat4x4			init_matroty(float ftheta);
t_mat4x4			init_matrotz(float ftheta);
t_mat4x4			mat_makeid(void);
t_mat4x4			mat_maketrans(float x, float y, float z);
t_mat4x4			mat_makeproj(float ffov, float fasr, float fne, float ffar);
t_vec3d				mat_mulvec(t_mat4x4 m, t_vec3d i);
t_mat4x4			mat_multmat(t_mat4x4 m1, t_mat4x4 m2);
t_mat4x4			mat_pointat(t_vec3d pos, t_vec3d target, t_vec3d up);
t_mat4x4			mat_quick_invert(t_mat4x4 m);
int					tri_clipping(t_vec3d pp, t_vec3d pn, t_tri ini, t_tri *cd);
float				dist(t_vec3d p, t_vec3d plane_n, t_vec3d plane_p);
void				clip_out_1(t_tri *clp, t_ctri tri, t_clip c);
void				clip_out_2(t_tri *clp, t_ctri tri, t_clip c, t_tri in_tri);
void				clip_in_1(t_tri *clp, t_ctri tri, t_clip c);
void				clip_in_2(t_tri *clp, t_ctri tri, t_clip c, t_tri in_tri);
int					clip_full_in_out(t_tri *clp, t_clip c, t_tri in_tri);
void				init_clip(t_vec3d *pp, t_vec3d *pn, t_clip *c, t_tri *i_i);
t_texture			*xpm_parser(t_texture *tex, int nb_tex);
void				xpm_header(t_texture *tex, t_tex_data *data, char *buff);
int					hex_to_dec(char *hex);
void				xpm_malloc(t_texture *tex, t_tex_data *data, int i);
void				fill_texture(t_tri ti, t_texture tx, t_depth *db, int noc);
t_tex_var			init_tex_var(t_tri tri, t_tex_var var);
t_tex_var			get_step(t_tex_var var);
t_tex_var			init_tex_var_second(t_tri tri, t_tex_var var);
t_tex_var			ax_bx(t_tex_var var);
t_tex_var			further_step(t_tex_var var, t_tri tri, int tok);
t_tri				sort_point(t_tri tri);
void				apply_texture(t_tex_var *var, t_texture tex, t_depth *deh);
#endif
