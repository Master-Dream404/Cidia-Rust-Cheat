#include "Projectile.h"
#include "Driver.h"
#include "global.h"
Projectile::Projectile(uintptr_t address) {
	this->Class = address;
	global::print(XR("[Projectile] Initialized"));

	/*
	uintptr_t projectile;
	int projectile_size;
	uintptr_t projectile_list;
	*/
}
// need a new bypass to changes values.
void Projectile::MoveProjectileShoot(Vector3 pos) {
	uintptr_t Projectile_list = driver::read<uintptr_t>(Class + 0x10);
	if (Projectile_list)
	{
		size_t Projectile_list_size = driver::read<size_t>( Class + 0x18 );
		for (int idx{ 0 }; idx < 1000; idx++)
		{
			uintptr_t Projectile = driver::read<uintptr_t>(Projectile_list + 0x20 + (idx * 0x8));
			if (!Projectile)
				continue;

			int projectileID_t = driver::read<int>(Projectile + projectileID);
			if (projectileID_t > 128)
			{
				std::cout << "projectileID: " << projectileID_t << " : " << idx << std::endl;
				std::cout << driver::read<float>( Projectile + maxDistance ) << std::endl;
				//driver::write(Projectile + maxDistance, 1000);
				//driver::write(Projectile + initialVelocity, pos);
			}
			Sleep(1);
			//Sleep(10);
		}
	}
}