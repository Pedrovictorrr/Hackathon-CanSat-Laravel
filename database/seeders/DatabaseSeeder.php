<?php

namespace Database\Seeders;

// use Illuminate\Database\Console\Seeds\WithoutModelEvents;
use Illuminate\Database\Seeder;
use App\Models\User;

class DatabaseSeeder extends Seeder
{
    /**
     * Seed the application's database.
     *
     * @return void
     */
    public function run()
    {
        User::create([
            'name' => 'Pedro Abreu',
            'email' => 'pedro.fabreu97@gmail.com',
            'password' => bcrypt('123456')
        ]);
        User::create([
            'name' => 'User Teste',
            'email' => 'teste@gmail.com',
            'password' => bcrypt('123456')
        ]);
    }
}
