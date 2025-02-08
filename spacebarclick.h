import { useState, useEffect } from "react";

export default function SpacebarClicker() {
  const [count, setCount] = useState(0);
  const [multiplier, setMultiplier] = useState(1);
  const [clicksPerSecond, setClicksPerSecond] = useState(0);
  const [upgrades, setUpgrades] = useState([
    { name: "Keyboard Chimp", cost: 20, rate: 0.2, owned: 0, description: "A chimp randomly hits the keyboard every 5 seconds." },
    { name: "Speedy Grandma", cost: 100, rate: 3, owned: 0, description: "A speedy grandma aggressively types at 3x a second!" },
    { name: "TikTok Pro", cost: 500, rate: 20, owned: 0, description: "A TikTok pro scrolling fast, pressing at 20x a second!" },
    { name: "Hyper Keyboard", cost: 6000, multiplier: 2, owned: 0, description: "Doubles your own hits!" },
    { name: "Broken Keyboard", cost: 7000, rate: 75, owned: 0, description: "A broken keyboard that spams spacebar at 75x per second!" },
    { name: "Alien Gun", cost: 10000, rate: 150, owned: 0, description: "A girl made a gun, but it malfunctioned, striking the keyboard at 150x per second!" }
  ]);

  const handleClick = () => setCount(Math.floor(count + multiplier));

  useEffect(() => {
    const interval = setInterval(() => {
      let totalRate = upgrades.reduce((sum, upgrade) => sum + upgrade.owned * (upgrade.rate || 0), 0);
      setClicksPerSecond(Math.floor(totalRate));
      setCount(prevCount => Math.floor(prevCount + totalRate));
    }, 1000);
    return () => clearInterval(interval);
  }, [upgrades]);

  const buyUpgrade = (index) => {
    if (count >= upgrades[index].cost) {
      setCount(Math.floor(count - upgrades[index].cost));
      const newUpgrades = [...upgrades];
      newUpgrades[index].owned++;
      newUpgrades[index].cost = Math.floor(newUpgrades[index].cost * 1.5);
      
      if (newUpgrades[index].name === "Hyper Keyboard") {
        setMultiplier(multiplier * 2);
      }
      
      setUpgrades(newUpgrades);
    }
  };

  return (
    <div className="flex flex-col items-center justify-center p-10 bg-[#f7f4e3] min-h-screen w-full text-[#3c2f2f] font-serif">
      <h1 className="text-7xl font-bold mb-2">{Math.floor(count)}</h1>
      <p className="text-xl mb-6">per second: {Math.floor(clicksPerSecond)}</p>
      <button 
        onClick={handleClick} 
        className="bg-[#b29f79] px-12 py-6 rounded-lg text-2xl font-bold shadow-lg border-2 border-[#3c2f2f]"
      >
        SPACEBAR
      </button>
      <div className="mt-10 w-full max-w-3xl space-y-4">
        {upgrades.sort((a, b) => a.cost - b.cost).map((upgrade, index) => (
          <div 
            key={index} 
            className={`w-full p-5 rounded-lg shadow-lg border-2 border-[#3c2f2f] flex justify-between items-center text-lg transition-all ${count >= upgrade.cost ? 'bg-[#e4d6b6] hover:bg-[#c9b38c] cursor-pointer' : 'bg-[#d3c4a1] cursor-not-allowed'}`}
            onClick={() => buyUpgrade(index)}
          >
            <div>
              <span className="font-bold">{upgrade.name}</span>
              <p className="text-sm">{upgrade.description}</p>
            </div>
            <div className="text-right">
              <span className="text-2xl font-bold">{upgrade.owned}</span>
              <p className="text-sm">{upgrade.cost} clicks</p>
            </div>
          </div>
        ))}
      </div>
    </div>
  );
}
