#include uniforms_fs

void main()
{
	gl_FragColor = vec4( u_color.rgb, 1.0 );
}
